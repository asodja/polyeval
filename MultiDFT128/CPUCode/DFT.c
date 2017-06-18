
#include <math.h>
#include <stdio.h>
#include "Maxfiles.h" 			// Includes .max files
#include <MaxSLiCInterface.h>	// Simple Live CPU interface
#include "common.h"
#include "multiparse.h"

#define PI 3.14159265


int areFloatsEqual(float first, float second, float epsilon) {
	if (fabs(first - second) < epsilon) {
		return 1;
	} else {
		return 0;
	}
}


void checkResult(uint32_t n, uint32_t m, float* xs, float* es, float* result) {
	printf("================================================\n");
	printf("Checking result\n");
	float* expected = malloc(sizeof(float) * n * m);

	int valid = 1;
	long double real = 0.0;
	for (uint32_t k = 0; k < m; k++) {
		uint32_t offset = k * n;
		for (uint32_t i = offset; i < offset + n; i++) {
			expected[i] = 0.0;
			for (uint32_t j = offset; j < offset + n; j++) {
				expected[i] += xs[j] * es[(i * j) % n];
			}
			if (areFloatsEqual(result[i], expected[i], 0.000001)) {
				printf("%f: result[%d] == expected[%d] ... %f == %f\n", xs[i], i, i, result[i], expected[i]);
			} else {
				printf("%f: result[%d] != expected[%d] ... %f != %f\n", xs[i], i, i, result[i], expected[i]);
				valid = 0;
			}
		}
	}
	if (valid) {
		printf("Result is correct\n");
	} else {
		printf("Result is incorrect\n");
	}
	printf("cpu-score: %Lf\n", real);
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
	float* points = get_random_oninterval_complex_array_as_float(m * n,  0.95, 1.05, 0.0, 0.01, seed + 1);
	// float* points = get_random_oninterval_float_array(n * m, 0.95, 1.05, seed + 1);
	// float* es = get_random_oninterval_float_array(n, 0.95, 1.05, seed + 1);
	// print_real_array(m, points, "POINTS");
	for (uint32_t i = 0; i < n * m; i++) {
	    //float real = ((rand() & 1) ? -1 : 1) * (rMinValue + ((float) rand() / (float) RAND_MAX) * (rMaxValue - rMinValue));
	    //float imaginary = ((rand() & 1) ? -1 : 1) * (iMinValue + ((float) rand() / (float) RAND_MAX) * (iMaxValue - iMinValue));
	    //constants[i][REAL] = real;
	    //constants[i][IMAG] = imaginary;
	    double theta = (double)i / (double) (n * 33) * PI;
	    points[i * 2] = 1.0 * cos(10.0 * theta) + 0.5 * cos(25.0 * theta);
	    points[i * 2 + 1] = 1.0 * sin(10.0 * theta) + 0.5 * sin(25.0 * theta);
	}
	//for (uint32_t i = 0; i < n * m; i++) {
	//	points[i * 2] = (float) i;
	//	points[i * 2 + 1] = 1;
	//	if (i < n) {
	//		es[i] = i;
	//	}
	//}
	//for (uint32_t i = 0; i < 2 * n * m; i+=2) {
	//	printf("%d: %f + i*%f\n", i / 2, points[i], points[i + 1]);
	//}


	// Setup result
	uint32_t tile_size = 16;
	uint32_t tick_count = 16;
	uint32_t n16 = (n - 1 + 16) / 16 * 16;
	float* result = malloc(sizeof(float) * n * m * 2);
	timing_t timer;
	timer_start(&timer);
	float* es = malloc(sizeof(float) * n * 2);
	for (uint32_t i = 0; i < n; i++) {
		float k = 2 * PI * i / (float) n;
		es[i * 2] = cos(k);
		es[i * 2 + 1] = -sin(k);
	}
	MultiDFT(m, n, n16, es, points, result);
	timer_stop(&timer);

	// checkResult(n, m, points, es, result);
	//printf("\n\n\n");
	//for (uint32_t i = 0; i < 2 * n * m; i+=2) {
	//	printf("%d: %f + i*%f\n", i / 2, result[i], result[i + 1]);
	//}
	long double real = 0.0;
	long double img = 0.0;
	for (uint32_t i = 0; i < 2 * n * m; i+=2) {
		// printf("%d: %f + i*%f\n", i, result[i], result[i + 1]);
		real += result[i];
		img += result[i + 1];
	}
	printf("n: %d, m: %d, t: %dms, r: %Lf + i*%Lf\n", n, m, timer.realtime, real, img);


	return 0;
}
