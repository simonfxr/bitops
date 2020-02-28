#ifndef BO_TEST_TESTING_H
#define BO_TEST_TESTING_H

#include <hu/annotations.h>
#include <hu/macros.h>

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include "rand.h"

static int TEST_PASSES = 0;
static int TEST_FAILURES = 0;
static int TEST_FAILED = 0;

static uint64_t RAND_SEED;
static pcg32_random_t RNG;

#define TEST_PP_SCOPED_DECL_(decl, flagname, final)                            \
    for (int flagname = 1; flagname;)                                          \
        for (decl; flagname; flagname = final)
#define TEST_PP_SCOPED_DECL(decl, final)                                       \
    TEST_PP_SCOPED_DECL_(decl, HU_CAT_COUNTER(test_scope_flag_), final)

#define TEST_GROUP(g)                                                          \
    TEST_PP_SCOPED_DECL(const char *const TEST_GROUP_NAME = g, 0)
#define TEST(t)                                                                \
    TEST_PP_SCOPED_DECL(const char *const TEST_NAME =                          \
                          test_begin(TEST_GROUP_NAME, t),                      \
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

static void
rand_init()
{
    RAND_SEED = hu_reinterpret_cast(uintptr_t, &printf);
    RAND_SEED *= 0xe61e4796a3073275ull;
    RAND_SEED ^= hu_reinterpret_cast(uintptr_t, &errno);
    printf("*** Using random seed: 0x%llx\n",
           hu_static_cast(unsigned long long, RAND_SEED));
}

static const char *
test_begin(const char *test_group, const char *test)
{
    TEST_FAILED = 0;
    uint64_t s0 = djb2_strhash(1, test_group);
    s0 = djb2_strhash(s0, "::");
    s0 = djb2_strhash(s0, test);
    RNG = rng_derive(RAND_SEED, s0);
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

#define RAND_W_u(W) bo_ucast(W, rng_rand_un(&RNG, W))
#define RAND_W_i(W) bo_icast(W, rng_rand_in(&RNG, W))
#define RAND_UI_W(UI, W) BO_AP(BO_CAT(RAND_W_, UI), W)

#endif
