
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
		constants[i] = (float) constant;
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
	float partialSum[16];
	for (uint32_t i = 0; i < 16 && i < n; i++) {
		partialSum[i] = summands[i];
	}
	for (uint32_t i = 16; i < n; i++) {
		partialSum[i % 16] += summands[i];
	}
	float sum = 0.0;
	for (uint32_t i = 0; i < 16; i++) {
		sum += partialSum[i];
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
	uint32_t n = 4096;
	float result[4];
	float* summands = getRandomFloatArray(n, 10.0);
	Sum(n, summands, result);

	printFloatArray(n, summands, "Summands");
	float actual = result[0];
	float expectedSum = cpuSum(n, summands);
	checkResult(actual, expectedSum);
	return 0;
}
