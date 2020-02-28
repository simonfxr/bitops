
#define REQUIRE_SEMI()                                                         \
    do {                                                                       \
    } while (0)

#define TEST_CONSISTENT_F_UI_W(F, UI, W)                                       \
    TEST(#F "_" #UI #W)                                                        \
    {                                                                          \
        for (int i = 0; !TEST_FAILED && i < RAND_ITER; ++i) {                  \
            BO_TYPE_UI_W(UI, W) x = RAND_UI_W(UI, W);                          \
            equal(bo_ptbl_##F##_##UI##W(x), bo_##F##_##UI##W(x));              \
        }                                                                      \
    }                                                                          \
    REQUIRE_SEMI()

#define TEST_CONSISTENT_F_UI(F, UI)                                            \
    TEST_CONSISTENT_F_UI_W(F, UI, 8);                                          \
    TEST_CONSISTENT_F_UI_W(F, UI, 16);                                         \
    TEST_CONSISTENT_F_UI_W(F, UI, 32);                                         \
    TEST_CONSISTENT_F_UI_W(F, UI, 64)

#define TEST_CONSISTENT_F(F)                                                   \
    TEST_CONSISTENT_F_UI(F, u);                                                \
    TEST_CONSISTENT_F_UI(F, i)

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

TEST_GROUP("consistency")
{
    TEST_CONSISTENT_F_UI(popcnt, u);
    TEST_CONSISTENT_F_UI(bswap, u);
    TEST_CONSISTENT_F_UI(rev, u);
    TEST_CONSISTENT_F_UI(ctz, u);
    TEST_CONSISTENT_F_UI(clz, u);
    TEST_CONSISTENT_F_UI(parity, u);
}
