
#include <stdint.h>
#include <stdio.h>
#include <sys/time.h>
#include <stdarg.h>
#include <getopt.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>


#include "common.h"

#define SHORTOPT "hn:m:"

#define PI 3.14159265

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

float complex* eval_dft(uint32_t n, uint32_t m, float complex* points, float complex* es) {
	float complex* expected = malloc(sizeof(float complex) * m * n);
	uint32_t p = 0;
	for (uint32_t i = 0; i < m * n; i+=n) {
		for (uint32_t k = 0; k < n; k++) {
			float complex sum = 0.0 + 0.0*I;
			uint32_t e_index = 0;
			for (uint32_t j = 0; j < n; j++) {
				float complex x = points[i + j];
				float complex e = es[e_index];
				e_index += k;
				e_index = (e_index >= n) ? e_index - n : e_index;
				sum += mul_complex(x, e);
			}
			expected[p++] = sum;
		}
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

	int seed = 15;
	float complex* points = malloc(sizeof(float complex) * n * m);
	for (uint32_t i = 0; i < n * m; i++) {
	    double theta = (double)i / (double) (n * 33) * PI;
	    float real = 1.0 * cos(10.0 * theta) + 0.5 * cos(25.0 * theta);
	    float imag = 1.0 * sin(10.0 * theta) + 0.5 * sin(25.0 * theta);
	    points[i] = real + imag * I;
	}

	timing_t timer;
	timer_start(&timer);
	float complex* es = malloc(sizeof(float complex) * n);
	for (uint32_t i = 0; i < n; i++) {
		float k = 2 * PI * i / (float) n;
		float real = cos(k);
		float img = -sin(k);
 		es[i] = real + img * I;
	}
	float complex* result = eval_dft(n, m, points, es);
 	timer_stop(&timer);
	
	long double real = 0.0;
	long double img = 0.0;
	for (uint32_t i = 0; i < n * m; i++) {
		real += crealf(result[i]);
		img += cimagf(result[i]);
	}
	printf("n: %d, m: %d, t: %dms, r: %Lf + i*%Lf\n", n, m, timer.realtime, real, img);

	return 0;
}

