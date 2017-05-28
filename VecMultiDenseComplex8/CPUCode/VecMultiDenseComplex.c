
#include <math.h>
#include <stdio.h>
#include "Maxfiles.h" 			// Includes .max files
#include <MaxSLiCInterface.h>	// Simple Live CPU interface
#include "common.h"
#include "multiparse.h"


int main(int argc, char * argv[])
{
	uint32_t* out = parse_args(argc, argv);
	uint32_t n = out[0]; // length of polynomial
	uint32_t m = out[1]; // number of xs
	if ((int32_t) n <= 0 || (int32_t) m <= 0) {
		error(1, "N and M cannot be less than 0", ' ');
	}

	int seed = 15;
	// Setup points, should be >= polynomial_length
	// and multiple of 16, so 16, 32, 48 etc.
	float* points = get_random_oninterval_complex_array_as_float(m,  0.95, 1.05, 0.0, 0.01, seed + 1);
	// print_complex_array(m, points, "POINTS");

	// Setup polynomials, size should be
	// of size 8, 12, 16, 20, 24, 28, 32 etc. <= 1024
	float* polynomial = get_random_oninterval_complex_array_as_float(n, 0, 5.0, 0, 0.5, seed);
	// print_dense_complex_poly(n, polynomial);

	// Setup result
	float* result = malloc(sizeof(float) * m * 2);
	timing_t timer;
	timer_start(&timer);
	VecMultiDenseComplex(m, n, polynomial, points, result);
	timer_stop(&timer);

	// print_complex_array(m, result, "Y");
	// checkResult(m, points, n, polynomial, result);

	long double real = 0.0;
	long double img = 0.0;
	for (uint32_t i = 0; i < m*2; i+=2) {
		real += result[i];
		img += result[i + 1];
	}
	printf("n: %d, m: %d, t: %dms, r: %Lf+%Lfi\n", n, m, timer.realtime, real, img);

	return 0;
}
