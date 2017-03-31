
#include "Maxfiles.h" 			// Includes .max files
#include <MaxSLiCInterface.h>	// Simple Live CPU interface
#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#include <sys/time.h>
#include <getopt.h>
#include "common.h"
#include "singleparse.h"


int main(int argc, char * argv[])
{
	uint32_t* out = parse_args(argc, argv);
	uint32_t n = out[0];
	if ((int32_t) n <= 0) {
		error(1, "N cannot be less than 0", ' ');
	}
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
	printf("[DF SINGLE POINT COMPLEX SPARSE]: n: %d, t: %dms, r: %f + %f*i\n", n, timer.realtime, result[0], result[1]);

	return 0;
}
