
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

void checkResult(uint32_t d, uint32_t n, uint32_t m, float* points, float* centers, uint64_t* result, float* result_min) {
	printf("================================================\n");
	printf("Checking result\n");
	uint64_t* expected = malloc(sizeof(uint64_t) * m);
	float* expected_min = malloc(sizeof(float) * m);
	for (uint32_t j = 0; j < m; j++) {
		float x_min = -1;
		uint64_t x_result = -1;
		int p_offset = j * d;
		for (uint32_t i = 0; i < n; i++) {
			float x_current = 0.0;
			int c_offset = i * d;
			for (uint32_t k = 0; k < d; k++) {
				float diff = points[p_offset+k] - centers[c_offset+k];
				x_current += (diff * diff);
			}
			if (i == 0 || x_current < x_min) {
				x_min = x_current;
				x_result = i;
			}

		}
		expected[j] = x_result;
		expected_min[j] = x_min;
	}

	int valid = 1;
	long double real = 0.0;
	for (uint32_t i = 0; i < m; i++) {
		real += expected[i];
		if (result[i] ==  expected[i]) {
			printf("%f: result[%d] == expected[%d] ... %d == %d, %f == %f\n", points[i], i, i, result[i], expected[i],
					result_min[i], expected_min[i]);
		} else {
			printf("%f: result[%d] != expected[%d] ... %d != %d,  %f != %f\n", points[i], i, i, result[i], expected[i],
					result_min[i], expected_min[i]);
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

float* reorder_data(float* points, uint64_t m, uint64_t d, int xsPerFragment) {
	float* reordered = malloc(sizeof(float) * m * d);
	uint64_t d_offset[d];
	for (int i = 0; i < d; i++) {
		d_offset[i] = xsPerFragment * i;
	}
	int counter = 0;
	int numOfXsInOneLoop = xsPerFragment*d;
	for (int k = 0; k < m; k+=numOfXsInOneLoop) {
		int offset = k;
		for (int i = 0; i < numOfXsInOneLoop && offset < m; i++) {
			for (int j = 0; j < d; j++) {
				printf("c: %d, k: %d, i: %d, j: %d, offset: %d\n", counter, k, i, j, (d_offset[j] + offset));
				fflush(stdout);
				reordered[d_offset[j] + offset] = points[counter++];
			}
			offset++;
		}
	}
	return reordered;
}

float* get_padded(float* points, uint32_t original_m, uint32_t m, uint32_t xsPerTick) {
	float* padded = malloc(sizeof(float) * xsPerTick);
	uint32_t point_index = m > original_m ? m - xsPerTick : m;
	for (uint32_t i = 0; i < xsPerTick; i++) {
		padded[i] = ((point_index + i) < original_m) ? points[point_index + i] : 0.0;
	}
	return padded;
}

float* reverse(float* original, uint32_t n) {
	float* reversed = malloc(sizeof(float) * n);
	for (uint32_t i = 0; i < n; i++) {
		reversed[n - i - 1] = original[i];
	}
	return reversed;
}

int main(int argc, char * argv[])
{
	uint32_t* out = parse_args(argc, argv);
	uint32_t n = out[0]; // length of centers
	uint32_t m = out[1]; // number of points
	uint32_t d = 2; // dimension
	if ((int32_t) n <= 0 || (int32_t) m <= 0 || (int32_t) d <= 0) {
		error(1, "N and M and D cannot be less than or eq 0", ' ');
	}

	int seed = 15;
	// Setup points, should be >= polynomial_length
	// and multiple of 16, so 16, 32, 48 etc.
	float* points = get_random_oninterval_with_dimension_float_array(m, d, 0, 100, seed + 1);
	// print_real_array(m * d, points, "POINTS");

	// Setup polynomials, size should be
	// of size 8, 12, 16, 20, 24, 28, 32 etc. <= 1024
	float* centers = get_random_oninterval_with_dimension_float_array(n, d, 0, 100, seed);
	// print_real_array(n * d, centers, "CENTERS");

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
	int xsPerTick = 64;
	int xsPerLoop = latency * xsPerTick;
	int tick_m = next_multiple_of(xsPerLoop, m);
	timing_t timer;
	timer_start(&timer);

	// Prepare padded points and results
	float* padded_points = malloc(sizeof(float) * d * xsPerLoop);
	uint64_t* result = malloc(sizeof(uint64_t) * m);
	float* result_min = malloc(sizeof(float) * m);

	// Run DFE
	// VecMultiDenseReal(m, n, tick_m, centers, points, result, result_min);
	max_file_t* mavMaxFile = KMeans_init();
	max_engine_t* mavDFE = max_load(mavMaxFile, "local:*");
	max_actions_t* actions = max_actions_init(mavMaxFile, "default");
	max_set_param_uint64t(actions, "m", m);
	max_set_param_uint64t(actions, "n", n);
	max_set_param_uint64t(actions, "tick_m", tick_m);
	max_queue_input(actions, "points", points, sizeof(float) * m * d);
	max_queue_input(actions, "points", padded_points, sizeof(float) * xsPerLoop * d);
	max_queue_input(actions, "centers", centers, sizeof(float) * n * d);
	max_queue_output(actions, "result", result, sizeof(uint64_t) * m);
	// max_queue_output(actions, "result_min", result_min, sizeof(float) * m);
	max_run(mavDFE, actions);
	max_actions_free(actions);
	max_unload(mavDFE);

	timer_stop(&timer);

	// checkResult(d, n, m, points, centers, result, result_min);
	long double real = 0.0;
	for (uint32_t i = 0; i < m; i++) {
		real += result[i];
	}
	printf("n: %d, m: %d, t: %dms, r: %Lf\n", n, m, timer.realtime, real);


	return 0;
}
