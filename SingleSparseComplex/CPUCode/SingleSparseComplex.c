
#include "Maxfiles.h" 			// Includes .max files
#include <MaxSLiCInterface.h>	// Simple Live CPU interface
#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#include <sys/time.h>
#include <getopt.h>
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

int main(int argc, char * argv[])
{
	parse_args(argc, argv);
	n = 16;
	int seed = 1;
	uint32_t maxExponent = 7;
	float maxConstant = 10;
	float xReal = 3.0f;
	float yImg = 4.0f;
	float* constants = get_random_float_array(n * 2, maxConstant, seed);
	uint32_t* exponents = get_random_uint_array(n, maxExponent, seed);
	print_dfe_sparse_complex(n, exponents, constants);

	timing_t timer;
	timer_start(&timer);
	float result[8];
	SinglePointEvaluation(n, xReal, yImg, constants, exponents, result);
 	timer_stop(&timer);
	free(constants);
	free(exponents);
	printf("[DF SINGLE POINT REAL SPARSE]: n: %d, t: %dms, r: %f + %f*i\n", n, timer.realtime, result[0], result[1]);

	return 0;
}
