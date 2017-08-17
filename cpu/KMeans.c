
#include <stdint.h>
#include <stdio.h>
#include <sys/time.h>
#include <stdarg.h>
#include <getopt.h>
#include <stdlib.h>
#include <float.h>


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

float* eval_multi_real_poly(uint32_t n, uint32_t m, float* polynomial, float* xs) {
	float* result = malloc(sizeof(float) * m);
	for (uint32_t j = 0; j < m; j++) {
		float x = xs[j];
		float x_result = 0.0f;
		for (uint32_t i = n; i > 0; i--) {
			x_result = x_result * x + polynomial[i - 1];
		}
		result[j] = x_result;
	}
	return result;
}

uint32_t* eval_kmeans(uint32_t n, uint32_t m, float* points, float* centers) {
	uint32_t* expected = malloc(sizeof(uint32_t) * m);
	for (uint32_t j = 0; j < m * 2; j+=2) {
		float x_min = FLT_MAX;
		uint32_t x_result = -1;
		float p_x = points[j];
		float p_y = points[j+1];
		for (uint32_t i = 0; i < n * 2; i+=2) {
			float c_x = centers[i];
			float c_y = centers[i+1];
			float diff_x = p_x - c_x;
			float diff_y = p_y - c_y;
			float sqDistance = (diff_x * diff_x) + (diff_y * diff_y);
			if (sqDistance < x_min) {
				x_min = sqDistance;
				x_result = i;
			}

		}
		expected[j >> 1] = (x_result >> 1);
		// expected_min[j] = x_min;
	}
	return expected;
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
	uint32_t d = 2;

	int seed = 15;
	float* points = get_random_oninterval_with_dimension_float_array(m, d, 0, 100, seed + 1);
	float* centers = get_random_oninterval_with_dimension_float_array(n, d, 0, 100, seed);

	timing_t timer;
	timer_start(&timer);
	uint32_t* expected = eval_kmeans(n, m, points, centers);
 	timer_stop(&timer);
	
	double r = 0.0;
	for (uint32_t i = 0; i < m; i++) {
		r += expected[i];
	}
	printf("n: %d, m: %d, t: %dms, r: %f\n", n, m, timer.realtime, r);

	return 0;
}

