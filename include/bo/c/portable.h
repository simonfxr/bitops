#ifndef BO_C_PORTABLE_H
#define BO_C_PORTABLE_H

#include <stdbool.h>
#include <stdint.h>

#define BO_CAT(x, y) x##y
#define BO_Q(...) (__VA_ARGS__)
#define BO_NIL /* empty */

#define BO_DEF_ALL(DEF) DEF(8) DEF(16) DEF(32) DEF(64)

#if defined(__cplusplus)
#    if __cplusplus >= 201103L
#        define BO_noexcept noexcept
#    endif
#    if __cplusplus >= 201402L
#        define BO_PTBL_CEXPR_P 1
#        define BO_cexpr /*constexpr*/
#    endif
#endif

#ifndef BO_cexpr
#    define BO_PTBL_CEXPR_P 0
#    define BO_cexpr
#endif

#ifndef BO_noexcept
#    define BO_noexcept
#endif

#define BO_PTBL_API /*inline*/ BO_cexpr

#define BO_DEF_I_FWD(W, nm)                                                    \
    BO_PTBL_API int##W##_t bo_ptbl_##nm##_i##W(int##W##_t x) BO_noexcept       \
    {                                                                          \
        return (int##W##_t) bo_ptbl_##nm##_u##W((uint##W##_t) x);              \
    }

#define BO_DEF_ALL_1(DEF, ...)                                                 \
    DEF(8, __VA_ARGS__)                                                        \
    DEF(16, __VA_ARGS__) DEF(32, __VA_ARGS__) DEF(64, __VA_ARGS__)

#define BO_DEF_PTBL_POPCNT(W)                                                  \
    BO_PTBL_API int bo_ptbl_popcnt_u##W(uint##W##_t x) BO_noexcept             \
    {                                                                          \
        int n = 0;                                                             \
        for (; x != 0; x &= x - 1)                                             \
            ++n;                                                               \
        return n;                                                              \
    }                                                                          \
                                                                               \
    BO_PTBL_API int bo_ptbl_popcnt_i##W(int##W##_t x)                          \
    {                                                                          \
        return bo_ptbl_popcnt_u##W((uint##W##_t) x);                           \
    }

BO_DEF_ALL(BO_DEF_PTBL_POPCNT)

#undef BO_DEF_PTBL_POPCNT

#define BO_DEF_ROL(W)                                                          \
    BO_PTBL_API uint##W##_t bo_ptbl_rol_u##W(uint##W##_t x, int n) BO_noexcept \
    {                                                                          \
        n &= W - 1;                                                            \
        return (x << n) | (x >> ((-n) & (W - 1)));                             \
    }

BO_DEF_ALL(BO_DEF_ROL)

#undef BO_DEF_ROL

#define BO_DEF_I_FWD_I(W, nm)                                                  \
    BO_PTBL_API int##W##_t bo_ptbl_##nm##_i##W(int##W##_t x, int n)            \
      BO_noexcept                                                              \
    {                                                                          \
        return (int##W##_t) bo_ptbl_##nm##_u##W((uint##W##_t) x, n);           \
    }

BO_DEF_ALL_1(BO_DEF_I_FWD_I, rol)

#define BO_DEF_ROR(W)                                                          \
    BO_PTBL_API uint##W##_t bo_ptbl_ror_u##W(uint##W##_t x, int n) BO_noexcept \
    {                                                                          \
        n &= W - 1;                                                            \
        return (x >> n) | (x << ((-n) & (W - 1)));                             \
    }

BO_DEF_ALL(BO_DEF_ROR)

#undef BO_DEF_ROR

BO_DEF_ALL_1(BO_DEF_I_FWD_I, ror)

BO_PTBL_API uint8_t
bo_ptbl_bswap_u8(uint8_t x) BO_noexcept
{
    return x;
}

BO_PTBL_API uint16_t
bo_ptbl_bswap_u16(uint16_t x) BO_noexcept
{
    return bo_ptbl_rol_u16(x, 8);
}

BO_PTBL_API uint32_t
bo_ptbl_bswap_u32(uint32_t x) BO_noexcept
{
    x = ((x & 0x00FF00FF) << 8) | ((x >> 8) & 0x00FF00FF);
    return bo_ptbl_rol_u32(x, 16);
}

BO_PTBL_API uint64_t
bo_ptbl_bswap_u64(uint64_t x) BO_noexcept
{
    x = ((x & 0x00FF00FF00FF00FF) << 8) | ((x >> 8) & 0x00FF00FF00FF00FF);
    x = ((x & 0x0000FFFF0000FFFF) << 16) | ((x >> 16) & 0x0000FFFF0000FFFF);
    return bo_ptbl_rol_u64(x, 32);
}

BO_DEF_ALL_1(BO_DEF_I_FWD, bswap)

BO_PTBL_API uint8_t
bo_ptbl_rev_u8(uint8_t x) BO_noexcept
{
    x = ((x & 0x55) << 1) | ((x >> 1) & 0x55);
    x = ((x & 0x33) << 2) | ((x >> 2) & 0xCC);
    return bo_ptbl_rol_u8(x, 4);
}

BO_PTBL_API uint16_t
bo_ptbl_rev_u16(uint16_t x) BO_noexcept
{
    x = ((x & 0x5555) << 1) | ((x >> 1) & 0x5555);
    x = ((x & 0x3333) << 2) | ((x >> 2) & 0x3333);
    x = ((x & 0x0F0F) << 4) | ((x >> 4) & 0x0F0F);
    return bo_ptbl_bswap_u16(x);
}

BO_PTBL_API uint32_t
bo_ptbl_rev_u32(uint32_t x) BO_noexcept
{
    x = ((x & 0x55555555) << 1) | ((x >> 1) & 0x55555555);
    x = ((x & 0x33333333) << 2) | ((x >> 2) & 0x33333333);
    x = ((x & 0x0F0F0F0F) << 4) | ((x >> 4) & 0x0F0F0F0F);
    return bo_ptbl_bswap_u32(x);
}

BO_PTBL_API uint64_t
bo_ptbl_rev_u64(uint64_t x) BO_noexcept
{
    x = ((x & 0x5555555555555555) << 1) | ((x >> 1) & 0x5555555555555555);
    x = ((x & 0x3333333333333333) << 2) | ((x >> 2) & 0x3333333333333333);
    x = ((x & 0x0F0F0F0F0F0F0F0F) << 4) | ((x >> 4) & 0x0F0F0F0F0F0F0F0F);
    return bo_ptbl_bswap_u64(x);
}

BO_DEF_ALL_1(BO_DEF_I_FWD, rev)

#define BO_DEF_PTBL_CTZ(W)                                                     \
    BO_PTBL_API int bo_ptbl_ctz_u##W(uint##W##_t x) BO_noexcept                \
    {                                                                          \
        if (!x)                                                                \
            return 8 * sizeof(x);                                              \
        x = (x ^ (x - 1)) >> 1;                                                \
        int n = 0;                                                             \
        for (; x; n++)                                                         \
            x >>= 1;                                                           \
        return n;                                                              \
    }                                                                          \
                                                                               \
    BO_PTBL_API int bo_ptbl_ctz_i##W(int##W##_t x) BO_noexcept                 \
    {                                                                          \
        return bo_ptbl_ctz_u##W((uint##W##_t) x);                              \
    }

BO_DEF_ALL(BO_DEF_PTBL_CTZ)

#undef BO_DEF_PTBL_CTZ

#define BO_DEF_PTBL_CLZ(W)                                                     \
    BO_PTBL_API int bo_ptbl_clz_u##W(uint##W##_t x) BO_noexcept                \
    {                                                                          \
        if (!x)                                                                \
            return 8 * sizeof(x);                                              \
        x = (x ^ (x - 1)) >> 1;                                                \
        int n = 0;                                                             \
        for (n = 0; (int##W##_t) x > 0; n++)                                   \
            x <<= 1;                                                           \
        return n;                                                              \
    }                                                                          \
                                                                               \
    BO_PTBL_API int bo_ptbl_clz_i##W(int##W##_t x) BO_noexcept                 \
    {                                                                          \
        return bo_ptbl_clz_u##W((uint##W##_t) x);                              \
    }

BO_DEF_ALL(BO_DEF_PTBL_CLZ)

#undef BO_DEF_PTBL_CLZ

#define BO_DEF_IS_POW2(W)                                                      \
    BO_PTBL_API bool bo_is_pow2_u##W(uint##W##_t x) BO_noexcept                \
    {                                                                          \
        return (x & (x - 1)) == 0;                                             \
    }                                                                          \
                                                                               \
    BO_PTBL_API bool bo_is_pow2_i##W(int##W##_t x) BO_noexcept                 \
    {                                                                          \
        return (x & (x - 1)) == 0;                                             \
    }

BO_DEF_ALL(BO_DEF_IS_POW2)

#undef BO_DEF_IS_POW2

BO_PTBL_API uint8_t
bo_ptbl_round_pow2_u8(uint8_t x) BO_noexcept
{
    --x;
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    ++x;
    return x;
}

BO_PTBL_API uint16_t
bo_ptbl_round_pow2_u16(uint16_t x) BO_noexcept
{
    --x;
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    ++x;
    return x;
}

BO_PTBL_API uint32_t
bo_ptbl_round_pow2_u32(uint32_t x) BO_noexcept
{
    --x;
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;
    ++x;
    return x;
}

BO_PTBL_API uint64_t
bo_ptbl_round_pow2_u64(uint64_t x) BO_noexcept
{
    --x;
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;
    x |= x >> 32;
    ++x;
    return x;
}

BO_PTBL_API bool
bo_ptbl_parity_u8(uint8_t x) BO_noexcept
{
    x ^= x >> 1;
    x ^= x >> 2;
    x ^= x >> 4;
    return x & 1;
}

BO_PTBL_API bool
bo_ptbl_parity_u16(uint16_t x) BO_noexcept
{
    x ^= x >> 1;
    x ^= x >> 2;
    x ^= x >> 4;
    x ^= x >> 8;
    return x & 1;
}

BO_PTBL_API bool
bo_ptbl_parity_u32(uint32_t x) BO_noexcept
{
    x ^= x >> 1;
    x ^= x >> 2;
    x ^= x >> 4;
    x ^= x >> 8;
    x ^= x >> 16;
    return x & 1;
}

BO_PTBL_API bool
bo_ptbl_parity_u64(uint64_t x) BO_noexcept
{
    x ^= x >> 1;
    x ^= x >> 2;
    x ^= x >> 4;
    x ^= x >> 8;
    x ^= x >> 16;
    x ^= x >> 32;
    return x & 1;
}

BO_DEF_ALL_1(BO_DEF_I_FWD, parity)

#endif
