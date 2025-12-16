#include "munit.h"

#include "tinyrand.h"

// Test seeding the random number generator
static MunitResult test_seed(const MunitParameter params[], void *data) {
  // Get a random seed for testing
  int64_t seedr = (int64_t)munit_rand_uint32();
  int64_t seedl = (int64_t)munit_rand_uint32();
  uint64_t seed = (seedl << 32) | seedr;

  // Create two seeded RNGs
  tinyrand_rng rng1 = new_rng_seeded(seed);
  tinyrand_rng rng2 = new_rng_seeded(seed);

  // Test that the first returned random number is the same between the 2
  munit_assert(tinyrand_next_uint64(&rng1) == tinyrand_next_uint64(&rng2));

  return MUNIT_OK;
}

// Create a list of tests for the test suite
static MunitTest tinyrand_suite_tests[] = {
    {.name = (char *)"Testing RNG Seeding",
     .test = test_seed,
     .setup = NULL,
     .tear_down = NULL,
     .options = MUNIT_TEST_OPTION_NONE,
     .parameters = NULL}};

// Create the test suite
static const MunitSuite tinyrand_suite = {.prefix = (char *)"Tinyrand Tests",
                                          .tests = tinyrand_suite_tests,
                                          .suites = NULL,
                                          .iterations = 10,
                                          .options = MUNIT_SUITE_OPTION_NONE};

// Main function for actually running the tests
int main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
  return munit_suite_main(&tinyrand_suite, NULL, argc, argv);
}
