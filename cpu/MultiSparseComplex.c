
#include <stdint.h>
#include <stdio.h>
#include <complex.h>
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

static inline float complex mul_complex(float complex first, float complex second) {
	float a = crealf(first);
	float b = cimagf(first);
	float c = crealf(second);
	float d = cimagf(second);
	return (a*c - b*d) + (b*c + a*d) * I; 
}

float complex pow_exp(float complex x, uint32_t e) {
	float complex result = 1.0f + 0.0f * I;
	while (e > 0) {
		if ((e & 1) != 0) {
			result = mul_complex(x, result);		
		}
		x = mul_complex(x, x);
		e = e >> 1;
	}
	return result;
}

float complex eval_single(uint32_t n, float complex* polynomial, uint32_t* exponents, float complex x) {
	float complex x_result = 0.0f;
	for (uint32_t i = 0; i < n; i++) {
		float complex powX = pow_exp(x, exponents[i]);
		x_result += mul_complex(polynomial[i], powX);
	}
	return x_result;
}

float complex* eval_multi_complex_poly(uint32_t n, uint32_t m, float complex* polynomial, uint32_t* exponents, float complex* xs) {
	float complex* result = malloc(sizeof(float complex) * m);
	for (uint32_t j = 0; j < m; j++) {
		result[j] = eval_single( n, polynomial, exponents,  xs[j]);
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
	float complex* constants = get_random_oninterval_complex_array(n, 0, 5.0, 0, 0.5, seed);
	float complex* xs = get_random_oninterval_complex_array(m, 0.95, 1.05, 0.0, 0.01, seed + 1);
	uint32_t* exponents = get_uint32_interval_array(n, 0);

	timing_t timer;
	timer_start(&timer);
	float complex* expected = eval_multi_complex_poly(n, m, constants, exponents, xs);
 	timer_stop(&timer);
	
	long double real = 0.0;
	long double img = 0.0;
	for (uint32_t i = 0; i < m; i++) {
		real += creal(expected[i]);
		img += cimag(expected[i]);
	}
	printf("n: %d, m: %d, t: %dms, r: %Lf+%Lfi\n", n, m, timer.realtime, real, img);

	return 0;
}
