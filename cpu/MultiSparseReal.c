
#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <sys/time.h>
#include <stdarg.h>
#include <getopt.h>
#include <stdlib.h>

#include "common.h"

#define SHORTOPT "hn:m:"


int help_flag = 0;

uint32_t n = 0;

uint32_t m = 0;

struct option options[] = {
   	{"help",    no_argument, &help_flag, 1},
	{"n",	required_argument, 0, 't'},
	{0, 0, 0, 0}
};

void error(const int status, const char * fmt, ...) {
    va_list argp;
    va_start(argp, fmt);
    fprintf(stderr, "error: ");
    vfprintf(stderr, fmt, argp);
    fprintf(stderr, "\n");
    va_end(argp);
    exit(status);
}

void help(const char * cmd) {
    printf("Usage: %s [filename]\n", cmd);
    printf("\nOptions:\n");
    printf("  -h, --help\n\tPrint short help\n");
    printf("  -n, --number-of-terms\n\tThis is length of polynomial\n");
    printf("  -m, --number-of-xs\n\tThis is number of xs to evaluate in\n");
}

void parse_args(int argc, char * argv[]) {
	// options
	while (1) {
		int option_index = 0;
		int opt = getopt_long(argc, argv, SHORTOPT, options, &option_index);
		if (opt == -1) break;
		switch (opt) {
		case 'h':
			help_flag = 1;
			break;
		case 'n':
			n = atoi(optarg);
			break;
		case 'm':
			m = atoi(optarg);
			break;
		case 0:
		break;
			case '?':
				error(1, "Invalid option '%c'", optopt);
			default:
				abort();
		}
	}
	// help?
	if (help_flag) {
		help(argv[0]);
		exit(0);
	}
}

float pow_exp(float x, uint32_t e) {
	float result = 1.0f;
	while (e > 0) {
		if ((e & 1) != 0) {
			result = x * result;		
		}
		x = x * x;
		e = e >> 1;
	}
	return result;
}

float eval_single(uint32_t n, float* polynomial, uint32_t* exponents, float x) {
	float x_result1 = 0.0f;
	float x_result2 = 0.0f;
	float x_result3 = 0.0f;
	float x_result4 = 0.0f;
	for (uint32_t i = 0; i < n; i+=4) {
		x_result1 += (polynomial[i] * pow_exp(x, exponents[i]));
		x_result2 += (polynomial[i+1] * pow_exp(x, exponents[i+1]));
		x_result3 += (polynomial[i+2] * pow_exp(x, exponents[i+2]));
		x_result4 += (polynomial[i+3] * pow_exp(x, exponents[i+3]));
	}
	return x_result1 + x_result2 + x_result3 + x_result4;
}

float* eval_multi_real_poly(uint32_t n, uint32_t m, float* polynomial, uint32_t* exponents, float* xs) {
	float* result = malloc(sizeof(float) * m);
	for (uint32_t j = 0; j < m; j+=4) {
		result[j] = eval_single(n, polynomial, exponents, xs[j]);
		result[j+1] = eval_single(n, polynomial, exponents, xs[j+1]);
		result[j+2] = eval_single(n, polynomial, exponents, xs[j+2]);
		result[j+3] = eval_single(n, polynomial, exponents, xs[j+3]);
	}
	return result;
}

int main(int argc, char * argv[])
{	
	parse_args(argc, argv);
	if (n <= 0) {
		error(1, "N cannot be 0", ' ');	
	}
	if (m <= 0) {
		error(1, "M cannot be 0", ' ');	
	}	

	int seed = 15;
	uint32_t maxExponent = 7;
	float maxConstant = 10;
	float* constants = get_random_oninterval_float_array(n, 0, 5.5, seed);
	float* xs = get_random_oninterval_float_array(m, 0.95, 1.05, seed + 1);
	uint32_t* exponents = get_uint32_interval_array(n, 0);

	timing_t timer;
	timer_start(&timer);
	float* expected = eval_multi_real_poly(n, m, constants, exponents, xs);
 	timer_stop(&timer);
	
	float r = 0.0;
	for (uint32_t i = 0; i < m; i++) {
		r += expected[i];
	}
	printf("n: %d, m: %d, t: %dms, r: %f\n", n, m, timer.realtime, r);

	return 0;
}
