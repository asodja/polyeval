
#include <math.h>
#include <stdio.h>
#include "Maxfiles.h" 			// Includes .max files
#include <MaxSLiCInterface.h>	// Simple Live CPU interface
#include "common.h"
#include "multiparse.h"


int areFloatsEqual(float first, float second, float epsilon) {
	if (fabs(first - second) < epsilon) {
		return 1;
	} else {
		return 0;
	}
}

void checkResult(uint32_t n_points, float* points, uint32_t polynomial_length, float* constants, uint32_t* exponents, float* result) {
	printf("================================================\n");
	printf("Checking result\n");
	float* expected = malloc(sizeof(float) * n_points);
	for (uint32_t i = 0; i < polynomial_length; i++) {
		for (uint32_t j = 0; j < n_points; j++) {
			if (i == 0) {
				expected[j] = 0;
			}
			expected[j] += constants[i] * powf(points[j], exponents[i]);
		}
	}

	int valid = 1;
	for (uint32_t i = 0; i < n_points; i++) {
		if (areFloatsEqual(result[i], expected[i], 0.00000001)) {
			printf("result[%d] == expected[%d] ... %f == %f\n", i, i, result[i], expected[i]);
		} else {
			printf("result[%d] != expected[%d] ... %f != %f\n", i, i, result[i], expected[i]);
			valid = 0;
		}
	}
	if (valid) {
		printf("Result is correct\n");
	} else {
		printf("Result is incorrect\n");
	}
}


int main(int argc, char * argv[])
{
	uint32_t* out = parse_args(argc, argv);
	uint32_t n = out[0];
	uint32_t m = out[1];
	if ((int32_t) n <= 0 || (int32_t) m <= 0) {
		error(1, "N and M cannot be less than 0", ' ');
	}

	float* xs = get_random_float_array(m * 2, 5.0, 2);
	print_complex_array(m, xs, "X");

	// Setup polynomials, size should be
	// of size 8, 12, 16, 20, 24, 28, 32 etc. <= 1024
	float* coefficients = get_random_float_array(n * 2, 5.0, 3);
	uint32_t* exponents = get_random_uint_array(n, 5, 1);
	print_sparse_complex_poly(n, coefficients, exponents);

	// Setup result
	float* result = malloc(sizeof(float) * m * 2);
	MultiSparseComplex(m, n, coefficients, exponents, xs, result);

	print_complex_array(m, result, "Result");


	return 0;
}
