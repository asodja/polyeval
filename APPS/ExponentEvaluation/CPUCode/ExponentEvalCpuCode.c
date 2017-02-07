
#include "Maxfiles.h" 			// Includes .max files
#include <MaxSLiCInterface.h>	// Simple Live CPU interface
#include <stdio.h>
#include <math.h>

float constants[8] = { 3, 3, 3, 3, 3, 3, 3, 3};
int32_t exponents[8] = { 3, 1, 0, 4, 1, 2, 7, 5};

float result[8];

int areFloatsEqual(float first, float second, float epsilon) {
	if (fabs(first - second) < epsilon) {
		return 1;
	} else {
		return 0;
	}
}

void checkResult(int32_t n, float* polynomial, int32_t* exponents, float x, float actual) {
	printf("================================================\n");
	printf("Checking result\n");
	float expected = 0.0;
	for (int32_t i = 0; i < n; i++) {
		expected += polynomial[i] * pow(x, exponents[i]);
	}

	printf("actual = %f, expected = %f\n", actual, expected);
	if (areFloatsEqual(actual, expected, 0.0000001)) {
		printf("Result is correct\n");
	} else {
		printf("Result is incorrect\n");
	}
}


int main()
{
	printf("Running DFE\n");
	ExponentEvaluation(constants, result);
	printf("Exponent result = %f\n", result[0]);

	return 0;
}
