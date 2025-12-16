#include "tinyrand.h"

// state of the splitmix generator
static uint64_t splitmix_state;
/*!
 * Simple splitmix generator, used for seeding the xoshiro256 generator */
uint64_t next_splitmix() {
  uint64_t z = (splitmix_state += 0x9e3779b97f4a7c15);
  z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
  z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
  return z ^ (z >> 31);
}

/*!
 * Rotate a 64-bit integer k values to the left
 *
 * @param x Integer to rotate
 * @param k number of positions to rotate*/
static inline uint64_t rol64(uint64_t x, int k) {
  return (x << k) | (x >> (64 - k));
}

// Use splitmix to set the seed state of the xorshiro generator
void tinyrand_seed(tinyrand_rng *rng, uint64_t seed) {
  splitmix_state = seed;

  for (int i = 0; i < 4; i++) {
    rng->state[i] = next_splitmix();
  }
}

// Generate an int value
uint64_t tinyrand_next_uint64(tinyrand_rng *rng) {
  uint64_t *state = rng->state;
  const uint64_t result = rol64(state[1] * 5, 7) * 9;

  const uint64_t t = state[1] << 17;

  state[2] ^= state[0];
  state[3] ^= state[1];
  state[1] ^= state[2];
  state[0] ^= state[3];

  state[2] ^= t;

  state[3] = rol64(state[3], 45);

  return result;
}

// Generate a floating point value
double tinyrand_next_double(tinyrand_rng *rng) {
  // NOTE:The random integer is first shifted 11 bits,
  // since double hold 53 bits of precision (actually
  // only holding 52 of the numbers since the last
  // is always one, since otherwise the exponent would
  // change). It is then multiplied by 1*10^-53,
  // to shift it into the range [0,1] since the random integer

  // Grabs the 53 highest significance bits,
  // and divides the resulting integer by 1x10^-53
  // to get a float in the range [0,1)
  return (tinyrand_next_uint64(rng) >> 11) * 0x1.0p-53;
}

// Create a new empty RNG struct
tinyrand_rng new_rng(void) {
  tinyrand_rng new_rng = {.state = {0, 0, 0, 0}};
  return new_rng;
};

// Create a new seeded RNG struct
tinyrand_rng new_rng_seeded(uint64_t seed) {
  tinyrand_rng new_rng = {.state = {0, 0, 0, 0}};
  tinyrand_seed(&new_rng, seed);

  return new_rng;
};
