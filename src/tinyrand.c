#include "tinyrand.h"

// state of the splitmix generator
static uint64_t splitmix_state;
/*!
 * Simple splitmix generator, used for seeding the xoshiro256 generator */
uint64_t next_splitmix(void) {
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

// The state of the generator
static uint64_t xorshiro256_state[4];

// Use splitmix to set the seed state of the xorshiro generator
void tinyrand_seed(uint64_t seed) {
  splitmix_state = seed;

  for (int i = 0; i < 4; i++) {
    xorshiro256_state[i] = next_splitmix();
  }
}

// Generate an int value
uint64_t tinyrand_next_int(void) {
  const uint64_t result = rol64(xorshiro256_state[1] * 5, 7) * 9;

  const uint64_t t = xorshiro256_state[1] << 17;

  xorshiro256_state[2] ^= xorshiro256_state[0];
  xorshiro256_state[3] ^= xorshiro256_state[1];
  xorshiro256_state[1] ^= xorshiro256_state[2];
  xorshiro256_state[0] ^= xorshiro256_state[3];

  xorshiro256_state[2] ^= t;

  xorshiro256_state[3] = rol64(xorshiro256_state[3], 45);

  return result;
}

// Generate a floating point value
double tinyrand_next_double(void) {
  // NOTE:The random integer is first shifted 11 bits,
  // since double hold 53 bits of precision (actually
  // only holding 52 of the numbers since the last
  // is always one, since otherwise the exponent would
  // change). It is then multiplied by 1*10^-53,
  // to shift it into the range [0,1] since the random integer
  //
  return (tinyrand_next_int() >> 11) * 0x1.0p-53;
}
