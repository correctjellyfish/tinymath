#include "munit.h"

#include "tinyrand.h"

typedef struct {
  uint64_t seed;
} tinyrand_test_data;

static tinyrand_test_data TEST_DATA;

// Function for setting up seed for the tests
static void *tinyrand_test_setup(const MunitParameter params[], void *data) {
  // Get a random seed for testing
  int64_t seedr = (int64_t)munit_rand_uint32();
  int64_t seedl = (int64_t)munit_rand_uint32();
  uint64_t seed = (seedl << 32) | seedr;
  tinyrand_test_data test_data = {.seed = seed};
  TEST_DATA = test_data;

  return (void *)&TEST_DATA;
}

// Test seeding the random number generator
static MunitResult test_seed(const MunitParameter params[], void *data) {
  tinyrand_test_data *test_data = (tinyrand_test_data *)data;

  // Create two seeded RNGs
  TinyrandRng rng1 = tinyrand_new_rng_seeded(test_data->seed);
  TinyrandRng rng2 = tinyrand_new_rng_seeded(test_data->seed);

  // Test that the first returned random number is the same between the 2
  munit_assert_uint64(tinyrand_next_uint64(&rng1), ==,
                      tinyrand_next_uint64(&rng2));

  return MUNIT_OK;
}

// Test generating random uint values
static MunitResult test_gen_uint64(const MunitParameter params[], void *data) {
  tinyrand_test_data *test_data = (tinyrand_test_data *)data;

  TinyrandRng test_rng = tinyrand_new_rng_seeded(test_data->seed);

  uint64_t first_rand_num = tinyrand_next_uint64(&test_rng);
  uint64_t second_rand_num = tinyrand_next_uint64(&test_rng);

  munit_assert_uint64(first_rand_num, !=, second_rand_num);

  return MUNIT_OK;
}

// Test generating random double values
static MunitResult test_gen_double(const MunitParameter params[], void *data) {
  tinyrand_test_data *test_data = (tinyrand_test_data *)data;

  TinyrandRng test_rng = tinyrand_new_rng_seeded(test_data->seed);

  double first_rand_num = tinyrand_next_double(&test_rng);
  double second_rand_num = tinyrand_next_double(&test_rng);

  // Test that the two random numbers are not equal
  munit_assert_double(first_rand_num, !=, second_rand_num);
  // Test that they are both between 0 and 1
  munit_assert_double(first_rand_num, >=, 0);
  munit_assert_double(first_rand_num, <=, 1);
  munit_assert_double(second_rand_num, >=, 0);
  munit_assert_double(second_rand_num, <=, 1);

  return MUNIT_OK;
}

// Create a list of tests for the test suite
static MunitTest tinyrand_suite_tests[] = {
    {.name = (char *)"Testing RNG Seeding",
     .test = test_seed,
     .setup = tinyrand_test_setup,
     .tear_down = NULL,
     .options = MUNIT_TEST_OPTION_NONE,
     .parameters = NULL},
    {.name = (char *)"Testing RNG Generation (uint64)",
     .test = test_gen_uint64,
     .setup = tinyrand_test_setup,
     .tear_down = NULL,
     .options = MUNIT_TEST_OPTION_NONE,
     .parameters = NULL},
    {.name = (char *)"Testing RNG Generation (double)",
     .test = test_gen_double,
     .setup = tinyrand_test_setup,
     .tear_down = NULL,
     .options = MUNIT_TEST_OPTION_NONE,
     .parameters = NULL},
};

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
