
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

float* get_padded(float* points, uint32_t original_m, uint32_t m, uint32_t xsPerTick) {
	float* padded = malloc(sizeof(float) * xsPerTick);
	uint32_t point_index = m > original_m ? m - xsPerTick : m;
	for (uint32_t i = 0; i < xsPerTick; i++) {
		padded[i] = ((point_index + i) < original_m) ? points[point_index + i] : 0.0;
	}
	return padded;
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
	float* points = get_random_oninterval_float_array(m, 0.95, 1.05, seed + 1);
	// print_real_array(m, points, "POINTS");

	// Setup polynomials, size should be
	// of size 8, 12, 16, 20, 24, 28, 32 etc. <= 1024
	float* polynomial = get_random_oninterval_float_array(n, 0, 5.5, seed);
	uint32_t* exponents = get_uint32_interval_array(n, 0);
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
	int latency = 16;
	int xsPerTick = 32;
	int num_of_padded = latency * xsPerTick;
	timing_t timer;
	timer_start(&timer);
	uint32_t original_m = m;
	m = next_multiple_of(num_of_padded, original_m);
	float* result = malloc(sizeof(float) * m);
	float* padded = get_padded(points, original_m, m, num_of_padded);
	VecMultiSparseReal(m, n, original_m, polynomial, exponents, padded, points, result);
	timer_stop(&timer);

	// checkResult(original_m, points, n, polynomial, result);
	long double real = 0.0;
	for (uint32_t i = 0; i < original_m; i++) {
		real += result[i];
	}
	printf("n: %d, m: %d, t: %dms, r: %Lf\n", n, original_m, timer.realtime, real);


	return 0;
}
