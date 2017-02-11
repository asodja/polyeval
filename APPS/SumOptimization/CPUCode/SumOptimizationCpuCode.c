
#include "Maxfiles.h" 			// Includes .max files
#include <MaxSLiCInterface.h>	// Simple Live CPU interface
#include <stdio.h>
#include <math.h>


void printFloatArray(uint32_t n, float* array, char* arrayName) {
	printf("================================================\n");
	printf("PRINTING FLOAT ARRAY '%s'\n", arrayName);
	for (uint32_t i = 0; i < n; i++) {
		printf("%s[%d] == %f\n", arrayName, i, array[i]);
	}
}

float* getRandomFloatArray(uint32_t n, float maxValue) {
	float* constants = malloc(sizeof(float) * n);
	for (uint32_t i = 0; i < n; i++) {
		float constant = ((float) rand() / (float) RAND_MAX) * maxValue;
		constants[i] = (float) (constant);
	}
	return constants;
}

int areFloatsEqual(float first, float second, float epsilon) {
	if (fabs(first - second) < epsilon) {
		return 1;
	} else {
		return 0;
	}
}

float cpuSum(uint32_t n, float* summands) {
	float sum = 0.0;
	for (uint32_t i = 0; i < n; i++) {
		sum += summands[i];
	}
	return sum;
}

void checkResult(float actual, float expected) {
	printf("================================================\n");
	printf("Checking result\n");
	printf("actual = %f, expected = %f\n", actual, expected);
	if (areFloatsEqual(actual, expected, 0.00001)) {
		printf("Result is correct\n");
	} else {
		printf("Result is incorrect\n");
	}
}

int main()
{
	double* r;
	printf("Running DFE\n");
	uint32_t n = 32;
	float result[4];
	float* summands = getRandomFloatArray(n, 10.0);
	Sum(n, summands, result);

	printFloatArray(n, summands, "Summands");
	float actualSum = result[0];
	float expectedSum = cpuSum(n, summands);
	checkResult(actualSum, expectedSum);
	return 0;
}
