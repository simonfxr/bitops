#ifndef BO_TESTING_H
#define BO_TESTING_H

#include <hu/annotations.h>
#include <hu/macros.h>

#include <stdio.h>
#include <stdlib.h>

static int TEST_PASSES = 0;
static int TEST_FAILURES = 0;
static int TEST_FAILED = 0;

#define TEST_PP_SCOPED_DECL_(decl, flagname, final)                            \
    for (int flagname = 1; flagname;)                                          \
        for (decl; flagname; flagname = final)
#define TEST_PP_SCOPED_DECL(decl, final)                                       \
    TEST_PP_SCOPED_DECL_(decl, HU_CAT_COUNTER(test_scope_flag_), final)

#define TEST_GROUP(g)                                                          \
    TEST_PP_SCOPED_DECL(const char *const TEST_GROUP_NAME = g, 0)
#define TEST(t)                                                                \
    TEST_PP_SCOPED_DECL(const char *const TEST_NAME = test_begin(t),           \
                        test_finish(TEST_GROUP_NAME, TEST_NAME))

#define assertMsg(b, msg)                                                      \
    if (!(b)) {                                                                \
        test_signal_failure(TEST_GROUP_NAME, TEST_NAME, __LINE__, msg);        \
        TEST_FAILED = 1;                                                       \
        continue;                                                              \
    }                                                                          \
    do {                                                                       \
    } while (0)

#define assert(b) assertMsg(b, "Expression is false: " #b)
#define equal(a, b) assertMsg((a) == (b), "Values do not match: " #a " != " #b)

static const char *
test_begin(const char *test)
{
    TEST_FAILED = 0;
    return test;
}

static int
test_finish(const char *testgroup, const char *test)
{
    if (!TEST_FAILED) {
        printf("*** TEST PASSED %s::%s\n", testgroup, test);
        ++TEST_PASSES;
    }
    return 0;
}

static void
test_signal_failure(const char *group,
                    const char *test,
                    int line,
                    const char *msg)
{
    fprintf(stderr,
            "*** TEST FAILED %s::%s at line %d\n*** MESSAGE: %s\n",
            group,
            test,
            line,
            msg);
    TEST_FAILURES++;
}

HU_NORETURN static void
test_exit()
{
    printf("PASSES: %d, FAILURES: %d\n", TEST_PASSES, TEST_FAILURES);
    exit(TEST_FAILURES > 0 ? EXIT_FAILURE : EXIT_SUCCESS);
}

#if HU_HAVE_NORETURN_P
#    define TEST_EXIT() test_exit()
#else
#    define TEST_EXIT()                                                        \
        do {                                                                   \
            test_exit();                                                       \
            return 0;                                                          \
        } while (0)
#endif

#endif
