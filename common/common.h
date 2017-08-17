#ifndef COMMON_H
#define COMMON_H

#include <time.h>
#include <sys/time.h>
#include <stdint.h>
#include <complex.h>

float* get_padded(float* points, uint32_t original_m, uint32_t m, uint32_t xsPerTick);

float* get_random_oninterval_with_dimension_float_array(uint32_t n, uint32_t d, float minValue, float maxValue, int seed);

float* get_padded_cplx(float* points, uint32_t original_m, uint32_t m, uint32_t xsPerTick);

uint32_t* get_uint32_interval_array(uint32_t n, uint32_t minValue);

float* get_random_float_array(uint32_t n, float maxValue, int seed);

float* get_random_oninterval_float_array(uint32_t n, float minValue, float maxValue, int seed);

float* adjust_float_array_size(uint32_t current_size, float* array, uint32_t new_size);

uint32_t next_multiple_of(uint32_t n, uint32_t larger_then);

float complex* get_random_complex_array(uint32_t n, float maxValue, int seed);

float complex* get_random_oninterval_complex_array(uint32_t n, float rMinValue, float rMaxValue, float iMinValue, float iMaxValue, int seed);

float* get_random_oninterval_complex_array_as_float(uint32_t n, float rMinValue, float rMaxValue, float iMinValue, float iMaxValue, int seed);

uint32_t* get_random_uint_array(uint32_t n, uint32_t maxValue, int seed);

void print_sparse_real_poly(uint32_t n, float* array, uint32_t* exponents);

void print_sparse_complex_poly(uint32_t n, float* array, uint32_t* exponents);

void print_cpe_sparse_complex_poly(uint32_t n, float complex* array, uint32_t* exponents);

void print_dense_real_poly(uint32_t n, float* polynomial);

void print_dense_complex_poly(uint32_t n, float* polynomial);

void print_real_array(uint32_t n, float* array, char* arrayName);

void print_complex_array(uint32_t n, float* array, char* arrayName);

void print_complex_number(float complex number);

#define PLAINTIMER

#ifdef __MACH__
#define PLAINTIMER
#endif

// timer_t is already used in time_h (Linux)
typedef struct timing_t {
#ifdef PLAINTIMER
    struct timeval realbegin, realend;
#else
    struct timespec realbegin, realend;
#endif
    clock_t cpubegin, cpuend;
    //
    clock_t realtime, cputime;  // in ms
} timing_t;

void timer_start(timing_t * t);

void timer_stop(timing_t * t);


#endif

