
#include "Maxfiles.h" 			// Includes .max files
#include <MaxSLiCInterface.h>	// Simple Live CPU interface
#include <stdio.h>
#include <math.h>
#include <sys/time.h>


static struct timeval tm1;

float* getRandomFloatArray(uint32_t n, float maxValue) {
	float* constants = malloc(sizeof(float) * n);
	for (uint32_t i = 0; i < n; i++) {
		float constant = ((float) rand() / (float) RAND_MAX) * maxValue;
		constants[i] = constant;
	}
	return constants;
}

uint32_t* getRandomUIntArray(uint32_t n, uint32_t maxValue) {
	uint32_t* values = malloc(sizeof(uint32_t) * n);
	for (uint32_t i = 0; i < n; i++) {
		values[i] = ((uint32_t) rand()) % maxValue;
	}
	return values;
}

int areFloatsEqual(float first, float second, float epsilon) {
	if (fabs(first - second) < epsilon) {
		return 1;
	} else {
		return 0;
	}
}

float getCpuValue(uint32_t n, float* polynomial, uint32_t* exponents, float x) {
	float partialResult[16];
	for (uint32_t i = 0; i < 16; i++) {
		partialResult[i] = polynomial[i] * powf(x, exponents[i]);
 	}
	for (uint32_t i = 16; i < n; i++) {
		partialResult[i % 16] += polynomial[i] * powf(x, exponents[i]);
	}
	float result = 0.0;
	for (uint32_t i = 0; i < 16; i++) {
		result += partialResult[i];
 	}
	return result;
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

static inline void start() {
    gettimeofday(&tm1, NULL);
}

static inline void stop() {
    struct timeval tm2;
    gettimeofday(&tm2, NULL);

    unsigned long long t = 1000 * (tm2.tv_sec - tm1.tv_sec) + (tm2.tv_usec - tm1.tv_usec) / 1000;
    printf("%llu ms\n", t);
}

int main()
{
	printf("Running DFE\n");
	uint32_t n = 64;
	uint32_t maxExponent = 5;
	float maxConstant = 20;
	float* constants = getRandomFloatArray(n, maxConstant);
	uint32_t* exponents = getRandomUIntArray(n, maxExponent);
	float x = 3.0f;
	float result[4];
	SinglePointEvaluation(n, x, constants, exponents, result);

	float actual = result[0];
	start();
	float expected = getCpuValue(n, constants, exponents, x);
	stop();
	checkResult(actual, expected);
	free(constants);
	free(exponents);

	return 0;
}
