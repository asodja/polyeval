
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


float complex* eval_multi_complex_poly(uint32_t n, uint32_t m, float complex* polynomial, uint32_t* exponents, float complex* xs) {
	float complex* result = malloc(sizeof(float complex) * m);
	for (uint32_t j = 0; j < m; j++) {
		float complex x = xs[j];
		float complex x_result = 0.0f + 0.0f * I;
		for (uint32_t i = 0; i < n; i++) {
			x_result += (polynomial[i] * (x == 0 && exponents[i] == 0 ? 1.0 : cpowf(x, exponents[i])));
		}
		result[j] = x_result;
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
	float complex* constants = get_random_complex_array(n, maxConstant, seed);
	float complex* xs = get_random_complex_array(m, maxConstant, seed+1);
	uint32_t* exponents = get_random_uint_array(n, maxExponent, seed+2);

	timing_t timer;
	timer_start(&timer);
	float complex* expected = eval_multi_complex_poly(n, m, constants, exponents, xs);
 	timer_stop(&timer);
	
	float complex r = 0.0;
	for (uint32_t i = 0; i < m; i++) {
		r += (float complex) expected[i];
	}
	printf("n: %d, m: %d, t: %dms, r: %f+%fi\n", n, m, timer.realtime, creal(r), cimag(r));

	return 0;
}
