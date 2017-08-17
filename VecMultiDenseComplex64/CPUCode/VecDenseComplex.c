
#include <math.h>
#include <stdio.h>
#include "Maxfiles.h" 			// Includes .max files
#include <MaxSLiCInterface.h>	// Simple Live CPU interface
#include "common.h"
#include "multiparse.h"


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
	long double real = 0.0;
	for (uint32_t i = 0; i < n_points; i++) {
		real += expected[i];
		if (areFloatsEqual(result[i], expected[i], 0.000001)) {
			printf("%f: result[%d] == expected[%d] ... %f == %f\n", points[i], i, i, result[i], expected[i]);
		} else {
			printf("%f: result[%d] != expected[%d] ... %f != %f\n", points[i], i, i, result[i], expected[i]);
			valid = 0;
		}
	}
	if (valid) {
		printf("Result is correct\n");
	} else {
		printf("Result is incorrect\n");
	}
	printf("cpu-score: %Lf\n", real);
}

float* reverse(float* original, uint32_t n) {
	float* reversed = malloc(sizeof(float) * n * 2);
	uint32_t nn = 2 * n;
	for (uint32_t i = 0; i < nn; i+=2) {
		reversed[nn - i - 1] = original[i + 1];
		reversed[nn - i - 2] = original[i];
	}
	return reversed;
}

int main(int argc, char * argv[])
{
	uint32_t* out = parse_args(argc, argv);
	uint32_t n = out[0]; // length of polynomial
	uint32_t m = out[1]; // number of xs
	if ((int32_t) n <= 0 || (int32_t) m <= 0) {
		error(1, "N and M cannot be less than 0", ' ');
	}

	int seed = 15;
	// Setup points, should be >= polynomial_length
	// and multiple of 16, so 16, 32, 48 etc.
	float* points = get_random_oninterval_complex_array_as_float(m,  0.95, 1.05, 0.0, 0.01, seed + 1);
	// print_complex_array(m, points, "POINTS");

	// Setup polynomials, size should be
	// of size 8, 12, 16, 20, 24, 28, 32 etc. <= 1024
	float* polynomial = get_random_oninterval_complex_array_as_float(n, 0, 5.0, 0, 0.5, seed);
	// print_dense_real_poly(n, polynomial);

	// We use poor man's padding because we read vectors:
    // We have two streams of points,
	// first stream "xs" are all xs that fall in multiple of xsPerTick,
    // second stream "padded_xs" are all xs that overflow multiple
	// (padded xs have last elements equal to 0)
    // Example: xsPerTick is 16, we have 41 xs:
    // - we will read first 32 xs from "xs" stream
    // - we will read last 9 xs from "padded_xs" stream
	//   ("padded_xs" stream has 7 padded zeros at the end)
	int latency = 36;
	int xsPerTick = 64;
	int num_of_padded = latency * xsPerTick;
	timing_t timer;
	timer_start(&timer);
	uint32_t original_m = m;
	m = next_multiple_of(num_of_padded, original_m);
	float* result = malloc(sizeof(float) * m * 2);
	float* padded = get_padded_cplx(points, original_m, m, num_of_padded);
	float* reversed = reverse(polynomial, n);
	VecMultiDenseComplex(m, n, original_m, reversed, padded, points, result);
	timer_stop(&timer);

	// checkResult(original_m, points, n, polynomial, result);
	long double real = 0.0;
	long double img = 0.0;
	for (uint32_t i = 0; i < original_m*2; i+=2) {
		real += result[i];
		img += result[i + 1];
	}
	printf("n: %d, m: %d, t: %dms, r: %Lf+%Lfi\n", n, original_m, timer.realtime, real, img);


	return 0;
}
