
#include <math.h>
#include <stdio.h>
#include "Maxfiles.h" 			// Includes .max files
#include <MaxSLiCInterface.h>	// Simple Live CPU interface
#include "common.h"
#include "multiparse.h"


float* getRandomFloatArray(uint32_t n, float maxValue) {
	float* constants = malloc(sizeof(float) * n);
	for (uint32_t i = 0; i < n; i++) {
		float constant = ((float) rand() / (float) RAND_MAX) * maxValue;
		constants[i] = (float) (constant);
	}
	return constants;
}

void printComplexArray(uint32_t n, float* array, char* arrayName) {
	printf("================================================\n");
	printf("PRINTING FLOAT ARRAY '%s'\n", arrayName);
	for (uint32_t i = 0; i < (n * 2); i+=2) {
		printf("%s[%d] == %f + %f * i\n", arrayName, i / 2, array[i], array[i + 1]);
	}
}

int areFloatsEqual(float first, float second, float epsilon) {
	if (fabs(first - second) < epsilon) {
		return 1;
	} else {
		return 0;
	}
}

void checkResult(uint32_t n_points, float* points, uint32_t polynomial_length, float* constants, float* result) {
	printf("================================================\n");
	printf("Checking result\n");
	float* expected = malloc(sizeof(float) * n_points);
	for (uint32_t j = 0; j < n_points; j++) {
		float x = points[j];
		float x_result = 0.0f;
		for (uint32_t i = polynomial_length; i > 0; i--) {
			x_result = x_result * x + constants[i - 1];
		}
		expected[j] = x_result;
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
	uint32_t n = out[0]; // length of polynomial
	uint32_t m = out[1]; // number of xs
	if ((int32_t) n <= 0 || (int32_t) m <= 0) {
		error(1, "N and M cannot be less than 0", ' ');
	}

	// Setup points, should be >= polynomial_length
	// and multiple of 16, so 16, 32, 48 etc.
	float* points = get_random_float_array(m * 2, 5.0, 2);
	printComplexArray(m * 2, points, "POINTS");

	// Setup polynomials, size should be
	// of size 8, 12, 16, 20, 24, 28, 32 etc. <= 1024
	float* polynomial = get_dfe_random_complex_array(n, 5.0, 3);
	print_dfe_dense_complex_rpoly(n, polynomial);

	// Setup result
	float* result = malloc(sizeof(float) * m * 2);
	MultiDenseReal(m, n, polynomial, points, result);

	printComplexArray(m, result, "Y");
	// checkResult(m, points, n, polynomial, result);

	return 0;
}
