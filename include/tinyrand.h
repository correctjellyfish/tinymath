#ifndef tinymath_tinyrand_h
#define tinymath_tinyrand_h

#include <stdint.h>

/*!
 * Seed the random number generator
 *
 * @param seed 64-bit integer seed */
void tinyrand_seed(uint64_t seed);

/*!
 * Generate a random 64-bit integer
 *
 * Uses the xoshiro256 RNG to generate a random
 * 64-bit integer
 *
 * @returns Random integer*/
uint64_t tinyrand_next_int(void);

/*!
 * Generate a random double
 *
 * Uses the xoshiro256 RNG to generate a random double
 * in the range [0,1]
 *
 * @returns Random double in range [0,1]*/
double tinyrand_next_double(void);

#endif
