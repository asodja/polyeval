
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

/*
void checkResult(uint32_t n, float* xs, uint32_t m, float* result) {
	printf("================================================\n");
	printf("Checking result\n");
	float* expected = malloc(sizeof(float) * n * m);

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
*/

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
	float* points = get_random_oninterval_float_array(n * m, 0.95, 1.05, seed + 1);
	// print_real_array(m, points, "POINTS");
	for (int i = 0; i < n * m; i++) {
		points[i] = (float) i + 1;
	}

	// Setup result
	uint32_t tile_size = 16;
	uint32_t tick_count = 16;
	uint32_t n16 = (n - 1 + 16) / 16 * 16;
	float* result = malloc(sizeof(float) * n * m);
	timing_t timer;
	timer_start(&timer);
	VecMultiDenseReal(m, n, n16, points, result);
	timer_stop(&timer);

	// checkResult(m, points, n, polynomial, result);
	long double real = 0.0;
	for (uint32_t i = 0; i < n * m; i++) {
		printf("%d: %f\n", i, result[i]);
		real += result[i];
	}
	printf("n: %d, m: %d, t: %dms, r: %Lf\n", n, m, timer.realtime, real);


	return 0;
}
