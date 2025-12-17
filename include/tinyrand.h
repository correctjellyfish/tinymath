#ifndef tinymath_tinyrand_h
#define tinymath_tinyrand_h

#include "tinycommon.h" // IWYU pragma: export

/*!
 * A Random Number Generator using the Xoshiro256 generator */
typedef struct {
  uint64_t state[4];
} TinyrandRng;

/*!
 * Create an empty RNG object
 *
 * @returns Empty RNG (state is empty, so must be seeded)
 * */
TinyrandRng tinyrand_new_rng(void);

/*!
 * Create a new seeded RNG object
 *
 * @param seed Number to use for seeding the RNG
 *
 * @returns A seeded RNG
 * */
TinyrandRng tinyrand_new_rng_seeded(uint64_t seed);

/*!
 * Seed the random number generator
 *
 * @param seed 64-bit integer seed */
void tinyrand_seed(TinyrandRng *rng, uint64_t seed);

/*!
 * Generate a random 64-bit integer
 *
 * Uses the xoshiro256 RNG to generate a random
 * 64-bit integer
 *
 * @returns Random integer*/
uint64_t tinyrand_next_uint64(TinyrandRng *rng);

/*!
 * Generate a random double
 *
 * Uses the xoshiro256 RNG to generate a random double
 * in the range [0,1]
 *
 * @returns Random double in range [0,1]*/
double tinyrand_next_double(TinyrandRng *rng);

#endif
