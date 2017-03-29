
#include <math.h>
#include <stdio.h>
#include "Maxfiles.h" 			// Includes .max files
#include <MaxSLiCInterface.h>	// Simple Live CPU interface
#include "common.h"


float* getRandomFloatArray(uint32_t n, float maxValue) {
	float* constants = malloc(sizeof(float) * n);
	for (uint32_t i = 0; i < n; i++) {
		float constant = ((float) rand() / (float) RAND_MAX) * maxValue;
		constants[i] = (float) (constant);
	}
	return constants;
}

void printFloatArray(uint32_t n, float* array, char* arrayName) {
	printf("================================================\n");
	printf("PRINTING FLOAT ARRAY '%s'\n", arrayName);
	for (uint32_t i = 0; i < n; i++) {
		printf("%s[%d] == %f\n", arrayName, i, array[i]);
	}
}

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

void printComplexArray(uint32_t n, float* array, char* arrayName) {
	printf("================================================\n");
	printf("PRINTING FLOAT ARRAY '%s'\n", arrayName);
	for (uint32_t i = 0; i < (n * 2); i+=2) {
		printf("%s[%d] == %f + %f * i\n", arrayName, i / 2, array[i], array[i + 1]);
	}
}

int main()
{
	printf("Running DFE\n");
	// Setup points, should be >= polynomial_length
	// and multiple of 16, so 16, 32, 48 etc.
	uint32_t m = 16;
	float* xs = get_random_float_array(m * 2, 5.0, 2);
	printComplexArray(m, xs, "Result");

	// Setup polynomials, size should be
	// of size 8, 12, 16, 20, 24, 28, 32 etc. <= 1024
	uint32_t n = 4;
	float* coefficients = get_random_float_array(n * 2, 5.0, 3);
	uint32_t* exponents = get_random_uint_array(n, 5, 1);
	print_dfe_sparse_complex_rpoly(n, exponents, coefficients);

	// Setup result
	float* result = malloc(sizeof(float) * m * 2);
	MultiSparseComplex(m, n, coefficients, exponents, xs, result);

	printComplexArray(m, result, "Result");


	return 0;
}
