
#include "bo/c/intrin.h"
#include "bo/c/portable.h"

#include <stdio.h>
#include <stdlib.h>

#define TEST_DECLARE_SCOPED_(decl, flagname)                                   \
    for (int flagname = 1; flagname;)                                          \
        for (decl; flagname; flagname = 0)
#ifdef __COUNTER__
#    define TEST_DECLARE_SCOPED(decl)                                          \
        TEST_DECLARE_SCOPED_(decl, BO_CAT1(test_scope_flag_, __COUNTER__))
#else
#    define TEST_DECLARE_SCOPED(decl)                                          \
        TEST_DECLARE_SCOPED_(decl, BO_CAT1(test_scope_flag_, __LINE__))
#endif

#define TEST_GROUP(g) TEST_DECLARE_SCOPED(const char *const TEST_GROUP_NAME = g)
#define TEST(t) TEST_DECLARE_SCOPED(const char *const TEST_NAME = t)

#define assertMsg(b, msg)                                                      \
    do {                                                                       \
        if (!(b))                                                              \
            test_failed(TEST_GROUP_NAME, TEST_NAME, __LINE__, msg);            \
    } while (0)

#define assert(b) assertMsg(b, "Expression is false: " #b)
#define equal(a, b) assertMsg((a) == (b), "Values do not match: " #a " != " #b)

static void
test_failed(const char *group, const char *test, int line, const char *msg)
{
    fprintf(stderr,
            "*** TEST %s::%s failed at line %d\n*** MESSAGE: %s\n",
            group,
            test,
            line,
            msg);
    exit(1);
}

int
main()
{
    TEST_GROUP("portable")
    {
        TEST("popcnt") { equal(bo_ptbl_popcnt_u8((uint8_t) 13), 3); }

        TEST("mul_u64")
        {
            bo_u128 prod =
              bo_ptbl_mul_u64(0xffffffffffffffffull, 0xffffffffffffffffull);
            bo_u128 res = { 0x1, 0xfffffffffffffffeull };
            equal(prod.lo, res.lo);
            equal(prod.hi, res.hi);
            assert(bo_ptbl_cmp_u128(&prod, &res) == 0);
        }
    }
    return 0;
}
