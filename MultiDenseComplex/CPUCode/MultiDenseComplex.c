
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

	// Setup points, should be >= polynomial_length
	// and multiple of 16, so 16, 32, 48 etc.
	float* points = get_random_float_array(m * 2, 5.0, 2);
	print_complex_array(m, points, "POINTS");

	// Setup polynomials, size should be
	// of size 8, 12, 16, 20, 24, 28, 32 etc. <= 1024
	float* polynomial = get_random_float_array(n * 2, 5.0, 3);
	print_dense_complex_poly(n, polynomial);

	// Setup result
	float* result = malloc(sizeof(float) * m * 2);
	MultiDenseReal(m, n, polynomial, points, result);

	print_complex_array(m, result, "Y");
	// checkResult(m, points, n, polynomial, result);

	return 0;
}
