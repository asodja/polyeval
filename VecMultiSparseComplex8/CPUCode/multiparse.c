#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#include <stdlib.h>
#include <sys/time.h>
#include <getopt.h>
#include "common.h"
#include "multiparse.h"


#define SHORTOPT "hn:m:"

struct option options[] = {
   	{"help",    no_argument, 0, 1},
	{"n",	required_argument, 0, 't'},
	{"m",	required_argument, 0, 't'},
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
    printf("  -m, --number-of-points to calculate Polynomial for\n");
}

uint32_t* parse_args(int argc, char * argv[]) {
	// options
	int help_flag = 0;
	uint32_t out[2];
	while (1) {
		int option_index = 0;
		int opt = getopt_long(argc, argv, SHORTOPT, options, &option_index);
		if (opt == -1) break;
		switch (opt) {
		case 'h':
			help_flag = 1;
			break;
		case 'n':
			out[0] = atoi(optarg);
			break;
		case 'm':
			out[1] = atoi(optarg);
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

	return out;
}
