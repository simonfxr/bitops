#include "bo/c/intrin.h"
#include "bo/c/portable.h"

#include "testing.h"

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

    TEST_EXIT();
}
