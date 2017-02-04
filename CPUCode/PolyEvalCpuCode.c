/**
 * Document: MaxCompiler Tutorial (maxcompiler-tutorial)
 * Chapter: 3      Example: 1      Name: Moving Average Simple
 * MaxFile name: MovingAverageSimple
 * Summary:
 *   CPU code for the three point moving average design.
 */
#include <time.h>
#include <stdlib.h>
#include "Maxfiles.h" 			// Includes .max files
#include <MaxSLiCInterface.h>	// Simple Live CPU interface

float* getConstants(int n, float maxValue) {
	srand(time(NULL));
	float* constants = malloc(sizeof(float) * n);
	for (int i = 0; i < n; i++) {
		float constant = ((float) rand() / (float) RAND_MAX) * maxValue;
		constants[i] = constant;
	}
	return constants;
}

int32_t* getExponents(int n, int32_t maxValue) {
	srand(time(NULL));
	int32_t* exponents =  malloc(sizeof(int32_t) * n);
	for (int i = 0; i < n; i++) {
		exponents[i] = rand() % maxValue;
	}
	return exponents;
}

void printIntArray(int* array, int n) {
	for (int i = 0; i < n; i++) {
		if (i == 0) {
			printf("{");
		}
		printf("%d", array[i]);
		if (i == n - 1) {
			printf("}\n");
		} else {
			printf(", ");
		}
	}
}

void printFloatArray(float* array, int n) {
	for (int i = 0; i < n; i++) {
		if (i == 0) {
			printf("{");
		}
		printf("%f", array[i]);
		if (i == n - 1) {
			printf("}\n");
		} else {
			printf(", ");
		}
	}
}

int main()
{
	printf("Running DFE\n");
	uint32_t maxExponents = 8;
	int32_t n = 256;
	float x = 3.0f;
	float* constants = getConstants(n, 15.0);
	int* exponents = getExponents(n, 15.0);
	float result[n];

	printf("Constants: ");
	printFloatArray(constants, n);
	printf("Exponents: ");
	printIntArray(exponents, n);

	PolyEval(n, constants, result);
	printFloatArray(result, n);

	return 0;
}
