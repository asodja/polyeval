
#include "Maxfiles.h" 			// Includes .max files
#include <MaxSLiCInterface.h>	// Simple Live CPU interface

float constants[8] = { 1, 0, 2, 0, 4, 1, 6, 3 };
int32_t exponents[8] = { 3, 1, 0, 4, 1, 2, 7, 5 };

float expVals[8] = { 1, 3, 9, 27, 81, 243, 729, 2187 };

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
	float sum = 0.0;
	for (uint32_t i = 0; i < n; i++) {
		sum += summands[i];
	}
	return sum;
}


int main()
{
	printf("Running DFE\n");
	uint32_t maxExponents = 8;
	int32_t n = 5000;
	float* summands = getRandomFloatArray(n, 10);
	float result[n];
	PolyEval(n, summands, result);

	for (int i = 0; i < n; i++) {
		printf("result[%d] = %f\n", i, result[i]);
	}
	printf("Polynomial result = %f\n", result[n - 1]);
	printf("CPU sum = %f\n", cpuSum(n, summands));

	return 0;
}
