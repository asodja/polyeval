#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>
#include <complex.h> 
#include "common.h"

float* get_random_float_array(uint32_t n, float maxValue, int seed) {
	srand(seed);
	float* constants = malloc(sizeof(float) * n);
	for (uint32_t i = 0; i < n; i++) {
		float constant = ((float) rand() / (float) RAND_MAX) * maxValue;
		constants[i] = (int) constant;
	}
	return constants;
}

float complex* get_random_complex_array(uint32_t n, float maxValue, int seed) {
	srand(seed);
	float complex* constants = malloc(sizeof(float complex) * n);
	for (uint32_t i = 0; i < n; i++) {
		float real = ((float) rand() / (float) RAND_MAX) * maxValue;
		float imaginary = ((float) rand() / (float) RAND_MAX) * maxValue;
		constants[i] = (int) real + (int) imaginary * I;
	}
	return constants;
}

float* get_dfe_random_complex_array(uint32_t n, float maxValue, int seed) {
	srand(seed);
	float* coefficients = malloc(sizeof(float complex) * n * 2);
	for (uint32_t i = 0; i < (n * 2); i+=2) {
		float real = ((float) rand() / (float) RAND_MAX) * maxValue;
		float imaginary = ((float) rand() / (float) RAND_MAX) * maxValue;
		coefficients[i] = (int) real;
		coefficients[i + 1] = (int) imaginary;
	}
	return coefficients;
}

uint32_t* get_random_uint_array(uint32_t n, uint32_t maxValue, int seed) {
	srand(seed);
	uint32_t* values = malloc(sizeof(uint32_t) * n);
	for (uint32_t i = 0; i < n; i++) {
		values[i] = ((uint32_t) rand()) % maxValue;
	}
	return values;
}


void print_sparse_real_poly(uint32_t n, float* polynomial, uint32_t* exponents) {
	for (uint32_t i = 0; i < n; i++) {
		if (i > 0) {
			printf(" + ");
		}
		printf("%f * x^(%d)", polynomial[i], exponents[i]);
		if (i >= n - 1) {
			printf("\n");
		}
	}
}

void print_sparse_complex_poly(uint32_t n, float* polynomial, uint32_t* exponents) {
	for (uint32_t i = 0; i < (n * 2); i+=2) {
		if (i > 0) {
			printf(" + ");
		}
		printf("(%f + %f * i) * x^(%d)", polynomial[i], polynomial[i + 1], exponents[i]);
	}
	printf("\n");
}

void print_dense_real_poly(uint32_t n, float* polynomial) {
	for (uint32_t i = 0; i < n; i++) {
		if (i > 0) {
			printf(" + ");
		}
		printf("%f * x^(%d)", polynomial[i], i);
	}
	printf("\n");
}

void print_dense_complex_poly(uint32_t n, float* polynomial) {
	for (uint32_t i = 0; i < (n * 2); i+=2) {
		if (i > 0) {
			printf(" + ");
		}
		printf("(%f + %f * i) * x^(%d)", polynomial[i], polynomial[i + 1], i / 2);
	}
}

void print_real_array(uint32_t n, float* array, char* arrayName) {
	printf("================================================\n");
	printf("PRINTING FLOAT ARRAY '%s'\n", arrayName);
	for (uint32_t i = 0; i < n; i++) {
		printf("%s[%d] == %f\n", arrayName, i, array[i]);
	}
}

void print_complex_array(uint32_t n, float* array, char* arrayName) {
	printf("================================================\n");
	printf("PRINTING COMPLEX ARRAY '%s'\n", arrayName);
	for (uint32_t i = 0; i < (n * 2); i+=2) {
		printf("%s[%d] == %f + %f * i\n", arrayName, i / 2, array[i], array[i + 1]);
	}
}

void print_complex_number(float complex number) {
	printf("%f+%fi\n", creal(number), cimag(number));
}

void timer_start(timing_t * t) {
#ifdef PLAINTIMER
    gettimeofday(&t->realbegin, NULL);
#else
    clock_gettime(CLOCK_MONOTONIC, &t->realbegin);
#endif
    t->cpubegin = clock();
}


void timer_stop(timing_t * t) {
#ifdef PLAINTIMER
    gettimeofday(&t->realend, NULL);
#else
    clock_gettime(CLOCK_MONOTONIC, &t->realend);
#endif
    t->cpuend = clock();
    // calculate the difference in ms
    t->realtime = (t->realend.tv_sec - t->realbegin.tv_sec) * 1000;
#ifdef PLAINTIMER
    t->realtime += (t->realend.tv_usec - t->realbegin.tv_usec) / 1000;
#else
    t->realtime += (t->realend.tv_nsec - t->realbegin.tv_nsec) / 1000;
#endif
    t->cputime = (t->cpuend - t->cpubegin) * 1000 / CLOCKS_PER_SEC;
}

