#include "munit.h"

#include "tinyadd.h"

static MunitResult test1(const MunitParameter params[], void *data) {
  int a = 1, b = 2, c = 4;

  munit_assert(tinyaddfn(a, b) == c);

  return MUNIT_OK;
}

static MunitTest test_suite_tests[] = {{
    .name = (char *)"simpletest1",
    .test = test1,
    .setup = NULL,
    .tear_down = NULL,
    .options = MUNIT_TEST_OPTION_NONE,
    .parameters = NULL,
}};

static const MunitSuite test_suite = {
    .prefix = (char *)"test_tinyadd_suite",
    .tests = test_suite_tests,
    .suites = NULL,
    .iterations = 1,
    .options = MUNIT_SUITE_OPTION_NONE,
};

int main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
  return munit_suite_main(&test_suite, (void *)"tinymathiscool", argc, argv);
}
