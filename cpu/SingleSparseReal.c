
#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <sys/time.h>
#include <stdarg.h>
#include <getopt.h>
#include <stdlib.h>

#include "common.h"

#define SHORTOPT "hn:"


int help_flag = 0;

uint32_t n = 0;

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

float eval_single_real_poly(uint32_t n, float* polynomial, uint32_t* exponents, float x) {
	float result = 0.0;
	for (uint32_t i = 0; i < n; i++) {
		result += polynomial[i] * pow_exp(x, exponents[i]);
	}
	return result;
}

int main(int argc, char * argv[])
{	
	parse_args(argc, argv);
	if (n <= 0) {
		error(1, "N cannot be 0", ' ');	
	}	

	int seed = 15;
	uint32_t maxExponent = 7;
	float maxConstant = 10;
	float x = 3.0f;
	float* constants = get_random_float_array(n, maxConstant, seed);
	uint32_t* exponents = get_random_uint_array(n, maxExponent, seed+1);

	timing_t timer;
	timer_start(&timer);
	float expected = eval_single_real_poly(n, constants, exponents, x);
 	timer_stop(&timer);

	printf("n: %d, t: %dms, r: %f\n", n, timer.realtime, expected);

	return 0;
}
