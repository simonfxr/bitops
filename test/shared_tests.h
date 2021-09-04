
#define REQUIRE_SEMI()                                                         \
    do {                                                                       \
    } while (0)

#define TEST_CONSISTENT_UI_F(UI, F, ...)                                       \
    F(UI, 8, __VA_ARGS__);                                                     \
    F(UI, 16, __VA_ARGS__);                                                    \
    F(UI, 32, __VA_ARGS__);                                                    \
    F(UI, 64, __VA_ARGS__)

#define TEST_CONSISTENT_F(...)                                                 \
    TEST_CONSISTENT_UI_F(u, __VA_ARGS__);                                      \
    TEST_CONSISTENT_UI_F(i, __VA_ARGS__)

#define TEST_CONSISTENT_UI_W_F1(UI, W, F)                                      \
    TEST(#F "_" #UI #W)                                                        \
    {                                                                          \
        for (int i = 0; !TEST_FAILED && i < rand_iter_for_bits(W); ++i) {      \
            BO_TYPE_UI_W(UI, W) x = RAND_UI_W(UI, W);                          \
            equal(bo_ptbl_##F##_##UI##W(x), bo_##F##_##UI##W(x));              \
        }                                                                      \
    }                                                                          \
    REQUIRE_SEMI()

#define TEST_CONSISTENT_UI_W_F2_I(UI, W, F)                                    \
    TEST(#F "_" #UI #W)                                                        \
    {                                                                          \
        for (int i = 0; !TEST_FAILED && i < rand_iter_for_bits(W); ++i) {      \
            int32_t n = RAND_UI_W(i, 32);                                      \
            BO_TYPE_UI_W(UI, W) x = RAND_UI_W(UI, W);                          \
            equal(bo_ptbl_##F##_##UI##W(x, n), bo_##F##_##UI##W(x, n));        \
        }                                                                      \
    }                                                                          \
    REQUIRE_SEMI()

#define TEST_CONSISTENT_UI_W_F3(UI, W, F)                                      \
    TEST(#F "_" #UI #W)                                                        \
    {                                                                          \
        for (int i = 0; !TEST_FAILED && i < rand_iter_for_bits(2 * W); ++i) {  \
            BO_TYPE_UI_W(UI, W) x = RAND_UI_W(UI, W);                          \
            BO_TYPE_UI_W(UI, W) y = RAND_UI_W(UI, W);                          \
            BO_TYPE_UI_W(UI, W) z1, z2;                                        \
            equal(bo_ptbl_##F##_##UI##W(x, y, &z1),                            \
                  bo_##F##_##UI##W(x, y, &z2));                                \
            equal(z1, z2);                                                     \
        }                                                                      \
    }                                                                          \
    REQUIRE_SEMI()

#define TEST_CONSISTENT_F1(F) TEST_CONSISTENT_F(TEST_CONSISTENT_UI_W_F1, F)
#define TEST_CONSISTENT_F2_I(F) TEST_CONSISTENT_F(TEST_CONSISTENT_UI_W_F2_I, F)
#define TEST_CONSISTENT_F3(F) TEST_CONSISTENT_F(TEST_CONSISTENT_UI_W_F3, F)

TEST_GROUP("portable")
{
    TEST("popcnt") { equal(bo_ptbl_popcnt_u8(13), 3); }

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
    TEST_CONSISTENT_F1(popcnt);
    TEST_CONSISTENT_F1(bswap);
    TEST_CONSISTENT_F1(rev);
    TEST_CONSISTENT_F1(ctz);
    TEST_CONSISTENT_F1(clz);
    TEST_CONSISTENT_F2_I(rol);
    TEST_CONSISTENT_F2_I(ror);
    TEST_CONSISTENT_F1(parity);
    TEST_CONSISTENT_F3(checked_add);
    TEST_CONSISTENT_F3(checked_sub);
}
