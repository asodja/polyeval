#ifndef COMMON_H
#define COMMON_H

#include <time.h>
#include <sys/time.h>
#include <stdint.h>
#include <complex.h>

float* get_random_float_array(uint32_t n, float maxValue, int seed);

float complex* get_random_complex_array(uint32_t n, float maxValue, int seed);

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
