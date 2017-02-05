
#include <math.h>
#include <stdio.h>
#include "Maxfiles.h" 			// Includes .max files
#include <MaxSLiCInterface.h>	// Simple Live CPU interface


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

void checkResult(uint32_t n_points, float* points, uint32_t polynomial_length, float* constants, float* result) {
	printf("================================================\n");
	printf("Checking result\n");
	float* expected = malloc(sizeof(float) * n_points);
	for (uint32_t i = 0; i < polynomial_length; i++) {
		for (uint32_t j = 0; j < n_points; j++) {
			if (i == 0) {
				expected[j] = 0;
			}
			expected[j] += constants[i] * points[j];
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

int main()
{
	printf("Running DFE\n");
	// Setup points, should be >= polynomial_length
	// and multiple of 20, so 20, 40, 60 etc.
	uint32_t number_of_points = 1000;
	float* points = getRandomFloatArray(number_of_points, 5.0);
	printFloatArray(number_of_points, points, "POINTS");

	// Setup polynomials, size should be
	// of size 20, 24, 28, 32 etc. <= 1024
	uint32_t polynomial_length = 20;
	float* constants = getRandomFloatArray(polynomial_length, 5.0);
	printFloatArray(polynomial_length, constants, "Polynomial");

	// Setup result
	float* result = malloc(sizeof(float) * number_of_points);
	MultiPointEvaluation(number_of_points, polynomial_length, constants, points, result);

	checkResult(number_of_points, points, polynomial_length, constants, result);


	return 0;
}
