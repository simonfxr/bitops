#ifndef BO_C_INTRIN_H
#define BO_C_INTRIN_H

#ifndef HU_ARCH_H
#    include <hu/arch.h>
#endif

#ifndef HU_BITS_H
#    include <hu/bits.h>
#endif

#ifndef HU_FEATURES_H
#    include <hu/features.h>
#endif

#ifndef HU_COMPILER_H
#    include <hu/compiler.h>
#endif

#ifndef BO_C_PORTABLE_H
#    include <bo/c/portable.h>
#endif

#if HU_ARCH_X86_P && hu_has_include(<x86intrin.h>)
#    include <x86intrin.h>
#    define BO_HAVE_X86_INTRIN_H_P 1
#else
#    define BO_HAVE_X86_INTRIN_H_P 0
#endif

#if HU_ARCH_X86_P && hu_has_include(<immintrin.h>)
#    include <immintrin.h>
#    define BO_HAVE_X86_IMMINTRIN_H_P 1
#else
#    define BO_HAVE_X86_IMMINTRIN_H_P 0
#endif

#if HU_COMP_MSVC_P
#    include <intrin.h>
#    include <stdlib.h> // _byteswap_XXX
#    define BO_HAVE_MSVC_INTRIN_H_P() 1
#else
#    define BO_HAVE_MSVC_INTRIN_H_P() 0
#endif

#if defined(__cplusplus) && hu_has_include(<bit>)
#    if __cplusplus > 201703L
#        include <bit>
#        define BO_HAVE_CXX_BIT_H_P() 1
#    endif
#endif

#ifndef BO_HAVE_CXX_BIT_H_P
#    define BO_HAVE_CXX_BIT_H_P() 0
#endif

#define BO_cexpr_if(P) BO_CAT(BO_cexpr_if_, P)

#define BO_cexpr_if_0
#define BO_cexpr_if_1 BO_cexpr

#define BO_INTRIN_API(CEXPR_P) BO_cexpr_if(CEXPR_P) BO_PTBL_API_WO_CEXPR
#define BO_INTRIN_API_WO_CEXPR BO_PTBL_API_WO_CEXPR

#define BO_INTRIN_API_F_W(F, W)                                                \
    BO_INTRIN_API(BO_CAT1(BO_CAT1(BO_CAT1(BO_CAT1(BO_, F), _U), W), _CEXPR_P))

#define BO_DEF_I_FWD(W, nm, nmu)                                               \
    BO_INTRIN_API_F_W(nmu, W)                                                  \
    int##W##_t bo_##nm##_i##W(int##W##_t x) BO_noexcept                        \
    {                                                                          \
        return bo_icast(W, bo_##nm##_u##W(bo_ucast(W, x)));                    \
    }

#define BO_DEF_I_FWD_INT(W, nm, nmu)                                           \
    BO_INTRIN_API_F_W(nmu, W)                                                  \
    int bo_##nm##_i##W(int##W##_t x) BO_noexcept                               \
    {                                                                          \
        return bo_##nm##_u##W(bo_ucast(W, x));                                 \
    }

#define BO_DEF_I_FWD_BOOL(W, nm, nmu)                                          \
    BO_INTRIN_API_F_W(nmu, W)                                                  \
    bool bo_##nm##_i##W(int##W##_t x) BO_noexcept                              \
    {                                                                          \
        return bo_##nm##_u##W(bo_ucast(W, x));                                 \
    }

#define BO_DEF_I_FWD_I(W, nm, nmu)                                             \
    BO_INTRIN_API_F_W(nmu, W)                                                  \
    int##W##_t bo_##nm##_i##W(int##W##_t x, int n) BO_noexcept                 \
    {                                                                          \
        return bo_icast(W, bo_##nm##_u##W(bo_ucast(W, x), n));                 \
    }

HU_BEGIN_EXTERN_C

#if BO_HAVE_CXX_BIT_H_P()
#    define BO_POPCNT_U32_IMPL std::popcount
#    define BO_POPCNT_U32_CEXPR_P 1
#    define BO_HAVE_POPCNT_U32_INTRIN_P() 0
#elif hu_has_builtin(__builtin_popcount) || HU_COMP_GNUC_P
#    define BO_POPCNT_U32_IMPL __builtin_popcount
#    define BO_POPCNT_U32_CEXPR_P 1
#    define BO_HAVE_POPCNT_U32_INTRIN_P() 1
#elif BO_HAVE_MSVC_INTRIN_H_P() && HU_ARCH_X86_P
#    define BO_POPCNT_U32_IMPL(x) (int) __popcnt(x)
#    define BO_POPCNT_U32_CEXPR_P 1
#    define BO_HAVE_POPCNT_U32_INTRIN_P() 1
#else
#    define BO_POPCNT_U32_IMPL bo_ptbl_popcnt_u32
#    define BO_POPCNT_U32_CEXPR_P BO_PTBL_CEXPR_P
#    define BO_HAVE_POPCNT_U32_INTRIN_P() 0
#endif

BO_INTRIN_API(BO_POPCNT_U32_CEXPR_P)
int
bo_popcnt_u32(uint32_t x) BO_noexcept
{
    return BO_POPCNT_U32_IMPL(x);
}

#if BO_HAVE_CXX_BIT_H_P()
#    define BO_POPCNT_U16_IMPL std::popcount
#    define BO_POPCNT_U16_CEXPR_P 1
#    define BO_HAVE_POPCNT_U16_INTRIN_P() 0
#elif BO_HAVE_MSVC_INTRIN_H_P() && HU_ARCH_X86_P
#    define BO_POPCNT_U16_IMPL(x) (int) __popcnt16(x)
#    define BO_POPCNT_U16_CEXPR_P 1
#    define BO_HAVE_POPCNT_U16_INTRIN_P() 1
#elif BO_HAVE_POPCNT_U32_INTRIN_P()
#    define BO_POPCNT_U16_IMPL(x) BO_POPCNT_U32_IMPL(bo_ucast(32, x))
#    define BO_POPCNT_U16_CEXPR_P BO_POPCNT_U32_CEXPR_P
#    define BO_HAVE_POPCNT_U16_INTRIN_P() 1
#else
#    define BO_POPCNT_U16_IMPL bo_ptbl_popcnt_u16
#    define BO_POPCNT_U16_CEXPR_P 1
#    define BO_HAVE_POPCNT_U16_INTRIN_P() 0
#endif

BO_INTRIN_API(BO_POPCNT_U16_CEXPR_P)
int
bo_popcnt_u16(uint16_t x) BO_noexcept
{
    return BO_POPCNT_U16_IMPL(x);
}

#if BO_HAVE_CXX_BIT_H_P()
#    define BO_POPCNT_U8_IMPL std::popcount
#    define BO_POPCNT_U8_CEXPR_P 1
#elif BO_HAVE_POPCNT_U16_INTRIN_P()
#    define BO_POPCNT_U8_IMPL(x) BO_POPCNT_U16_IMPL(bo_ucast(32, x))
#    define BO_POPCNT_U8_CEXPR_P BO_POPCNT_U16_CEXPR_P
#else
#    define BO_POPCNT_U8_IMPL bo_ptbl_popcnt_u8
#    define BO_POPCNT_U8_CEXPR_P 1
#endif

BO_INTRIN_API(BO_POPCNT_U8_CEXPR_P)
int
bo_popcnt_u8(uint8_t x) BO_noexcept
{
    return BO_POPCNT_U8_IMPL(x);
}

#if BO_HAVE_CXX_BIT_H_P()
#    define BO_POPCNT_U64_IMPL std::popcount
#    define BO_POPCNT_U64_CEXPR_P 1
#elif hu_has_builtin(__builtin_popcountll) || HU_COMP_GNUC_P
#    define BO_POPCNT_U64_IMPL(x)                                              \
        __builtin_popcountll(bo_cast(unsigned long long, x))
#    define BO_POPCNT_U64_CEXPR_P 1
#elif BO_HAVE_MSVC_INTRIN_H_P() && HU_ARCH_X86_P && HU_BITS_64_P
#    define BO_POPCNT_U64_IMPL(x) (int) __popcnt64(x)
#    define BO_POPCNT_U64_CEXPR_P 1
#elif BO_HAVE_POPCNT_U32_INTRIN_P()
#    define BO_POPCNT_U64_IMPL(x)                                              \
        BO_POPCNT_U32_IMPL(bo_ucast(W, x)) +                                   \
          BO_POPCNT_U32_IMPL(bo_ucast(32, x >> 32))
#    define BO_POPCNT_U64_CEXPR_P BO_POPCNT_U32_CEXPR_P
#else
#    define BO_POPCNT_U64_IMPL bo_ptbl_popcnt_u64
#    define BO_POPCNT_U64_CEXPR_P BO_PTBL_CEXPR_P
#endif

BO_INTRIN_API(BO_POPCNT_U64_CEXPR_P)
int
bo_popcnt_u64(uint64_t x) BO_noexcept
{
    return BO_POPCNT_U64_IMPL(x);
}

BO_DEF_ALL_3(BO_DEF_I_FWD_INT, popcnt, POPCNT)

#define BO_BSWAP_U8_CEXPR_P 1

BO_INTRIN_API(BO_BSWAP_U8_CEXPR_P)
uint8_t
bo_bswap_u8(uint8_t x) BO_noexcept
{
    return x;
}

#if hu_has_builtin(__builtin_bswap16) || HU_COMP_GNUC_P
#    define BO_BSWAP_U16_IMPL __builtin_bswap16
#    define BO_BSWAP_U16_CEXPR_P 1
#elif HU_COMP_MSVC_P
#    define BO_BSWAP_U16_IMPL _byteswap_ushort
#    define BO_BSWAP_U16_CEXPR_P 1
#else
#    define BO_BSWAP_U16_IMPL bo_ptbl_bswap_u16
#    define BO_BSWAP_U16_CEXPR_P BO_PTBL_CEXPR_P
#endif

BO_INTRIN_API(BO_BSWAP_U16_CEXPR_P)
uint16_t
bo_bswap_u16(uint16_t x) BO_noexcept
{
    return BO_BSWAP_U16_IMPL(x);
}

#if hu_has_builtin(__builtin_bswap32) || HU_COMP_GNUC_P
#    define BO_BSWAP_U32_IMPL __builtin_bswap32
#    define BO_BSWAP_U32_CEXPR_P 1
#elif HU_COMP_MSVC_P
#    define BO_BSWAP_U32_IMPL(x)                                               \
        (uint32_t) _byteswap_ulong(bo_cast(unsigned long, x))
#    define BO_BSWAP_U32_CEXPR_P 1
#else
#    define BO_BSWAP_U32_IMPL bo_ptbl_bswap_u32
#    define BO_BSWAP_U32_CEXPR_P BO_PTBL_CEXPR_P
#endif

BO_INTRIN_API(BO_BSWAP_U32_CEXPR_P)
uint32_t
bo_bswap_u32(uint32_t x) BO_noexcept
{
    return BO_BSWAP_U32_IMPL(x);
}

#if hu_has_builtin(__builtin_bswap64) || HU_COMP_GNUC_P
#    define BO_BSWAP_U64_IMPL __builtin_bswap64
#    define BO_BSWAP_U64_CEXPR_P 1
#elif HU_COMP_MSVC_P
#    define BO_BSWAP_U64_IMPL(x)                                               \
        bo_ucast(64, _byteswap_uint64(bo_cast(unsigned __int64, x)))
#    define BO_BSWAP_U64_CEXPR_P 1
#else
#    define BO_BSWAP_U64_IMPL bo_ptbl_bswap_u64
#    define BO_BSWAP_U64_CEXPR_P BO_PTBL_CEXPR_P
#endif

BO_INTRIN_API(BO_BSWAP_U64_CEXPR_P)
uint64_t
bo_bswap_u64(uint64_t x) BO_noexcept
{
    return BO_BSWAP_U64_IMPL(x);
}

BO_DEF_ALL_3(BO_DEF_I_FWD, bswap, BSWAP)

#if HU_ARCH_ARM_P
#    if HU_BITS_64_P
#        define ARM_ASM_OP32 "w"
#    else
#        define ARM_ASM_OP32
#    endif
#endif

#if hu_has_builtin(__builtin_bitreverse32)
#    define BO_REV_U32_IMPL(x) return __builtin_bitreverse32(x)
#    define BO_REV_U32_CEXPR_P 0
#elif HU_ARCH_ARM_P && HU_COMP_MSVC_P && HU_BITS_32_P
#    define BO_INTRIN_REV_U32_IMPL(x, n) (_arm_rbit(x) >> (32 - n))
#    define BO_REV_U32_CEXPR_P 0
#elif HU_ARCH_ARM_P && HU_COMP_GNUC_P
BO_INTRIN_API_WO_CEXPR uint32_t
bo_asm_rev_u32(uint32_t x) BO_noexcept
{
    uint32_t ret;
    __asm__("rbit %" ARM_ASM_OP32 "0, %" ARM_ASM_OP32 "1" : "=r"(ret) : "r"(x));
    return ret;
}
#    define BO_INTRIN_REV_U32_IMPL(x, n)                                       \
        ((__builtin_constant_p(x) ? bo_ptbl_rev_u32(x) : bo_asm_rev_u32(x)) >> \
         (32 - n))
#    define BO_REV_U32_CEXPR_P 0
#else
#    define BO_REV_U32_IMPL(x)                                                 \
        BO_BYTE_REV(32);                                                       \
        return bo_bswap_u32(x)
#    define BO_REV_U32_CEXPR_P BO_PTBL_CEXPR_P
#endif

#ifdef BO_INTRIN_REV_U32_IMPL
#    define BO_REV_U32_IMPL(x) return BO_INTRIN_REV_U32_IMPL(x, 32)
#endif

BO_INTRIN_API(BO_REV_U32_CEXPR_P)
uint32_t
bo_rev_u32(uint32_t x) BO_noexcept
{
    BO_REV_U32_IMPL(x);
}

#if hu_has_builtin(__builtin_bitreverse8)
#    define BO_REV_U8_IMPL(x) return __builtin_bitreverse8(x)
#    define BO_REV_U8_CEXPR_P 0
#elif defined(BO_INTRIN_REV_U32_IMPL)
#    define BO_REV_U8_IMPL(x) return BO_INTRIN_REV_U32_IMPL(x, 8)
#    define BO_REV_U8_CEXPR_P BO_REV_U32_CEXPR_P
#else
#    define BO_REV_U8_IMPL(x) return bo_ptbl_rev_u8(x)
#    define BO_REV_U8_CEXPR_P BO_PTBL_CEXPR_P
#endif

BO_INTRIN_API(BO_REV_U8_CEXPR_P)
uint8_t
bo_rev_u8(uint8_t x) BO_noexcept
{
    BO_REV_U8_IMPL(x);
}

#if hu_has_builtin(__builtin_bitreverse16)
#    define BO_REV_U16_IMPL(x) return __builtin_bitreverse16(x)
#    define BO_REV_U16_CEXPR_P 0
#elif defined(BO_INTRIN_REV_U32_IMPL)
#    define BO_REV_U16_IMPL(x) return BO_INTRIN_REV_U32_IMPL(x, 16)
#    define BO_REV_U16_CEXPR_P BO_REV_U32_CEXPR_P
#else
#    define BO_REV_U16_IMPL(x)                                                 \
        BO_BYTE_REV(16);                                                       \
        return bo_bswap_u16(x)
#    define BO_REV_U16_CEXPR_P BO_PTBL_CEXPR_P
#endif

BO_INTRIN_API(BO_REV_U16_CEXPR_P)
uint16_t
bo_rev_u16(uint16_t x) BO_noexcept
{
    BO_REV_U16_IMPL(x);
}

#if hu_has_builtin(__builtin_bitreverse64)
#    define BO_REV_U64_IMPL(x) return __builtin_bitreverse64(x)
#    define BO_REV_U64_CEXPR_P 0
#elif HU_ARCH_ARM_P && HU_COMP_GNUC_P && HU_BITS_64_P
BO_INTRIN_API_WO_CEXPR uint64_t
bo_asm_rev_u64(uint64_t x) BO_noexcept
{
    uint64_t ret;
    __asm__("rbit %0, %1" : "=r"(ret) : "r"(x));
    return ret;
}
#    define BO_REV_U64_IMPL(x)                                                 \
        return (__builtin_constant_p(x) ? bo_ptbl_rev_u64(x)                   \
                                        : bo_asm_rev_u64(x))
#    define BO_REV_U64_CEXPR_P 0
#elif defined(BO_INTRIN_REV_U32_IMPL)
#    define BO_REV_U64_IMPL(x)                                                 \
        uint32_t lo = bo_ucast(32, x);                                         \
        uint32_t hi = bo_ucast(32, (x) >> 32);                                 \
        lo = BO_INTRIN_REV_U32_IMPL(lo, 32);                                   \
        hi = BO_INTRIN_REV_U32_IMPL(hi, 32);                                   \
        return (hu_ucast(64, lo) << 32) | hi;
#    define BO_REV_U64_CEXPR_P BO_REV_U32_CEXPR_P
#else
#    define BO_REV_U64_IMPL(x)                                                 \
        BO_BYTE_REV(64);                                                       \
        return bo_bswap_u64(x)
#    define BO_REV_U64_CEXPR_P BO_PTBL_CEXPR_P
#endif

BO_INTRIN_API(BO_REV_U64_CEXPR_P)
uint64_t
bo_rev_u64(uint64_t x) BO_noexcept
{
    BO_REV_U64_IMPL(x);
}

BO_DEF_ALL_3(BO_DEF_I_FWD, rev, REV)

#if hu_has_builtin(__builtin_ctz) || HU_COMP_GNUC_P
#    define BO_CTZNZ_U32_IMPL(x) __builtin_ctz(x)
#    define BO_CTZ_U32_IMPL(x)                                                 \
        int y = BO_CTZNZ_U32_IMPL(x);                                          \
        return (x) != 0 ? y : 32
#    define BO_CTZ_U32_CEXPR_P 1
#    define BO_HAVE_CTZ_U32_INTRIN_P() 1
#else
#    define BO_CTZ_U32_IMPL(x) return bo_ptbl_ctz_u32(x)
#    define BO_CTZ_U32_CEXPR_P BO_PTBL_CEXPR_P
#    define BO_HAVE_CTZ_U32_INTRIN_P() 0
#endif

BO_INTRIN_API(BO_CTZ_U32_CEXPR_P)
int
bo_ctz_u32(uint32_t x) BO_noexcept
{
    BO_CTZ_U32_IMPL(x);
}

#if hu_has_builtin(__builtin_ctzs)
#    define BO_CTZNZ_U16_IMPL(x) __builtin_ctzs(x)
#    define BO_CTZ_U16_IMPL(x)                                                 \
        int y = BO_CTZNZ_U16_IMPL(x);                                          \
        return (x) != 0 ? y : 16
#    define BO_CTZ_U16_CEXPR_P 1
#    define BO_HAVE_CTZ_U16_INTRIN_P() 1
#elif BO_HAVE_CTZ_U32_INTRIN_P()
#    define BO_CTZNZ_U16_IMPL(x) BO_CTZNZ_U32_IMPL((x) | 0x10000u)
#    define BO_CTZ_U16_CEXPR_P BO_CTZ_U32_CEXPR_P
#    define BO_CTZ_U16_IMPL(x) return BO_CTZNZ_U16_IMPL(x)
#    define BO_HAVE_CTZ_U16_INTRIN_P() 1
#else
#    define BO_CTZ_U16_IMPL(x) return bo_ptbl_ctz_u16(x)
#    define BO_CTZ_U16_CEXPR_P BO_PTBL_CEXPR_P
#    define BO_HAVE_CTZ_U16_INTRIN_P() 0
#endif

BO_INTRIN_API(BO_CTZ_U16_CEXPR_P)
int
bo_ctz_u16(uint16_t x) BO_noexcept
{
    BO_CTZ_U16_IMPL(x);
}

#if BO_HAVE_CTZ_U16_INTRIN_P()
#    define BO_CTZ_U8_IMPL(x) BO_CTZNZ_U16_IMPL((x) | bo_ucast(16, 0x100u))
#    define BO_CTZ_U8_CEXPR_P BO_CTZ_U16_CEXPR_P
#else
#    define BO_CTZ_U8_IMPL bo_ptbl_ctz_u8
#    define BO_CTZ_U8_CEXPR_P BO_PTBL_CEXPR_P
#endif

BO_INTRIN_API(BO_CTZ_U8_CEXPR_P)
int
bo_ctz_u8(uint8_t x) BO_noexcept
{
    return BO_CTZ_U8_IMPL(x);
}

#if hu_has_builtin(__builtin_ctzll) || HU_COMP_GNUC_P
#    define BO_CTZ_U64_IMPL(x)                                                 \
        int n = __builtin_ctzll(x);                                            \
        return (x) != 0 ? n : 64
#    define BO_CTZ_U64_CEXPR_P 1
#elif BO_HAVE_CTZ_U32_INTRIN_P()
#    define BO_CTZ_U64_IMPL(x)                                                 \
        uint32_t lo = bo_ucast(32, x);                                         \
        if (lo != 0)                                                           \
            return BO_CTZNZ_U32_IMPL(lo);                                      \
        return bo_ctz_u32(bo_ucast(32, (x) >> 32))
#    define BO_CTZ_U64_CEXPR_P BO_CTZ_U32_CEXPR_P
#else
#    define BO_CTZ_U64_IMPL(x) return bo_ptbl_ctz_u64(x)
#    define BO_CTZ_U64_CEXPR_P BO_PTBL_CEXPR_P
#endif

BO_INTRIN_API(BO_CTZ_U64_CEXPR_P)
int
bo_ctz_u64(uint64_t x) BO_noexcept
{
    BO_CTZ_U64_IMPL(x);
}

BO_DEF_ALL_3(BO_DEF_I_FWD_INT, ctz, CTZ)

#if hu_has_builtin(__builtin_clz) || HU_COMP_GNUC_P
#    define BO_CLZNZ_U32_IMPL(x) __builtin_clz(x)
#    define BO_CLZ_U32_IMPL(x)                                                 \
        int y = BO_CLZNZ_U32_IMPL(x);                                          \
        return (x) != 0 ? y : 32
#    define BO_CLZ_U32_CEXPR_P 1
#    define BO_HAVE_CLZ_U32_INTRIN_P() 1
#else
#    define BO_CLZ_U32_IMPL(x) return bo_ptbl_clz_u32(x)
#    define BO_CLZ_U32_CEXPR_P BO_PTBL_CEXPR_P
#    define BO_HAVE_CLZ_U32_INTRIN_P() 0
#endif

BO_INTRIN_API(BO_CLZ_U32_CEXPR_P) int bo_clz_u32(uint32_t x) BO_noexcept
{
    BO_CLZ_U32_IMPL(x);
}

#if hu_has_builtin(__builtin_clzs)
#    define BO_CLZNZ_U16_IMPL(x) __builtin_clzs(bo_ucast(16, x))
#    define BO_CLZ_U16_IMPL(x)                                                 \
        int y = BO_CLZNZ_U16_IMPL(x);                                          \
        return (x) != 0 ? y : 16
#    define BO_CLZ_U16_CEXPR_P 1
#    define BO_HAVE_CLZ_U16_INTRIN_P() 1
#elif BO_HAVE_CLZ_U32_INTRIN_P()
#    define BO_CLZNZ_U16_IMPL(x)                                               \
        BO_CLZNZ_U32_IMPL((bo_ucast(32, x) << 16) | 0x8000u)
#    define BO_CLZ_U16_IMPL(x) return BO_CLZNZ_U16_IMPL(x)
#    define BO_CLZ_U16_CEXPR_P BO_CLZ_U32_CEXPR_P
#    define BO_HAVE_CLZ_U16_INTRIN_P() 1
#else
#    define BO_CLZ_U16_IMPL(x) return bo_ptbl_clz_u16(x)
#    define BO_CLZ_U16_CEXPR_P BO_PTBL_CEXPR_P
#    define BO_HAVE_CLZ_U16_INTRIN_P() 0
#endif

BO_INTRIN_API(BO_CLZ_U16_CEXPR_P)
int
bo_clz_u16(uint16_t x) BO_noexcept
{
    BO_CLZ_U16_IMPL(x);
}

#if BO_HAVE_CLZ_U16_INTRIN_P()
#    define BO_CLZ_U8_IMPL(x) BO_CLZNZ_U16_IMPL(bo_ucast(16, (x) << 8) | 0x80u)
#    define BO_CLZ_U8_CEXPR_P BO_CLZ_U16_CEXPR_P
#else
#    define BO_CLZ_U8_IMPL bo_ptbl_clz_u8
#    define BO_CLZ_U8_CEXPR_P BO_PTBL_CEXPR_P
#endif

BO_INTRIN_API(BO_CLZ_U8_CEXPR_P)
int
bo_clz_u8(uint8_t x) BO_noexcept
{
    return BO_CLZ_U8_IMPL(x);
}

#if hu_has_builtin(__builtin_clzll) || HU_COMP_GNUC_P
#    define BO_CLZ_U64_IMPL(x)                                                 \
        int n = __builtin_clzll(x);                                            \
        return (x) != 0 ? n : 64
#    define BO_CLZ_U64_CEXPR_P 1
#elif BO_HAVE_CLZ_U32_INTRIN_P()
#    define BO_CLZ_U64_IMPL(x)                                                 \
        do {                                                                   \
            uint32_t hi = bo_ucast(32, (x) >> 32);                             \
            if (hi != 0)                                                       \
                return BO_CLZNZ_U32_IMPL(hi);                                  \
            return bo_clz_u32(bo_ucast(32, x));                                \
        } while (0)
#    define BO_CLZ_U64_CEXPR_P BO_CLZ_U32_CEXPR_P
#else
#    define BO_CLZ_U64_IMPL(x) return bo_ptbl_clz_u64(x)
#    define BO_CLZ_U64_CEXPR_P BO_PTBL_CEXPR_P
#endif

BO_INTRIN_API(BO_CLZ_U64_CEXPR_P)
int
bo_clz_u64(uint64_t x) BO_noexcept
{
    BO_CLZ_U64_IMPL(x);
}

BO_DEF_ALL_3(BO_DEF_I_FWD_INT, clz, CLZ)

#if hu_has_builtin(__builtin_parity) || HU_COMP_GNUC_P
#    define BO_PARITY_U32_IMPL(x) __builtin_parity((x))
#    define BO_PARITY_U32_CEXPR_P 1
#    define BO_HAVE_PARITY_U32_INTRIN_P() 1
#else
#    define BO_PARITY_U32_IMPL bo_ptbl_parity_u32
#    define BO_PARITY_U32_CEXPR_P BO_PTBL_CEXPR_P
#    define BO_HAVE_PARITY_U32_INTRIN_P() 0
#endif

BO_INTRIN_API(BO_PARITY_U32_CEXPR_P)
bool
bo_parity_u32(uint32_t x) BO_noexcept
{
    return BO_PARITY_U32_IMPL(x);
}

#if BO_HAVE_PARITY_U32_INTRIN_P()
#    define BO_PARITY_U16_IMPL(x) BO_PARITY_U32_IMPL(x)
#    define BO_PARITY_U16_CEXPR_P BO_PARITY_U32_CEXPR_P
#else
#    define BO_PARITY_U16_IMPL bo_ptbl_parity_u16
#    define BO_PARITY_U16_CEXPR_P BO_PTBL_CEXPR_P
#endif

BO_INTRIN_API(BO_PARITY_U16_CEXPR_P)
bool
bo_parity_u16(uint16_t x) BO_noexcept
{
    return BO_PARITY_U16_IMPL(x);
}

#define BO_PARITY_U8_CEXPR_P 1

BO_INTRIN_API(BO_PARITY_U8_CEXPR_P)
bool
bo_parity_u8(uint8_t x) BO_noexcept
{
    return bo_ptbl_parity_u8(x);
}

#if hu_has_builtin(__builtin_parityll) || HU_COMP_GNUC_P
#    define BO_PARITY_U64_IMPL(x) __builtin_parityll(x)
#    define BO_PARITY_U64_CEXPR_P 1
#else
#    define BO_PARITY_U64_IMPL bo_ptbl_parity_u64
#    define BO_PARITY_U64_CEXPR_P BO_PTBL_CEXPR_P
#endif

BO_INTRIN_API(BO_PARITY_U64_CEXPR_P)
bool
bo_parity_u64(uint64_t x) BO_noexcept
{
    return BO_PARITY_U64_IMPL(x);
}

BO_DEF_ALL_3(BO_DEF_I_FWD_BOOL, parity, PARITY)

#define BO_DEF_CHECKED_OP(W, UI, nm, OP)                                       \
    BO_PTBL_API                                                                \
    bool bo_checked_##nm##_##UI##W(BO_TYPE_UI_W(UI, W) x,                      \
                                   BO_TYPE_UI_W(UI, W) y,                      \
                                   BO_TYPE_UI_W(UI, W) * z) BO_noexcept        \
    {                                                                          \
        OP(W, UI);                                                             \
    }

#if HU_GNUC_PREREQ(5, 0, 0) || hu_has_builtin(__builtin_add_overflow)
#    define BO_DEF_CHECKED_ADD_OP(W, UI)                                       \
        BO_TYPE_UI_W(UI, W) rr = 0;                                            \
        bool ret = !__builtin_add_overflow(x, y, &rr);                         \
        if (z)                                                                 \
            *z = rr;                                                           \
        return ret
#else
#    define BO_DEF_CHECKED_ADD_OP(W, UI)                                       \
        return bo_ptbl_checked_add_##UI##W(x, y, z)
#endif

BO_DEF_ALL_4(BO_DEF_CHECKED_OP, u, add, BO_DEF_CHECKED_ADD_OP)
BO_DEF_ALL_4(BO_DEF_CHECKED_OP, i, add, BO_DEF_CHECKED_ADD_OP)

#if HU_GNUC_PREREQ(5, 0, 0) || hu_has_builtin(__builtin_sub_overflow)
#    define BO_DEF_CHECKED_SUB_OP(W, UI)                                       \
        BO_TYPE_UI_W(UI, W) rr = 0;                                            \
        bool ret = !__builtin_sub_overflow(x, y, &rr);                         \
        if (z)                                                                 \
            *z = rr;                                                           \
        return ret
#else
#    define BO_DEF_CHECKED_SUB_OP(W, UI)                                       \
        return bo_ptbl_checked_sub_##UI##W(x, y, z)
#endif

BO_DEF_ALL_4(BO_DEF_CHECKED_OP, u, sub, BO_DEF_CHECKED_SUB_OP)
BO_DEF_ALL_4(BO_DEF_CHECKED_OP, i, sub, BO_DEF_CHECKED_SUB_OP)

#ifdef __SIZEOF_INT128__
#    define BO_HAVE_INT128_P 1
#else
#    define BO_HAVE_INT128_P 0
#endif

#if BO_HAVE_INT128_P
#    define BO_MUL_U64_IMPL(x, y)                                              \
        do {                                                                   \
            unsigned __int128 xy = bo_cast(unsigned __int128, x) * (y);        \
            prod.lo = bo_ucast(64, xy);                                        \
            prod.hi = bo_ucast(64, xy >> 64);                                  \
        } while (0)
#    define BO_MUL_U64_CEXPR_P 1
#elif BO_HAVE_MSVC_INTRIN_H_P() && HU_ARCH_X86_P && HU_BITS_64_P
#    define BO_MUL_U64_IMPL(x, y) prod.lo = _umul128((x), (y), &prod.hi)
#    define BO_MUL_U64_CEXPR_P 0
#elif BO_HAVE_MSVC_INTRIN_H_P() && HU_ARCH_X86_P && HU_BITS_32_P
#    define BO_MUL_U64_IMPL(x, y) BO_PTBL_MUL_U64(x, y, __emulu)
#    define BO_MUL_U64_CEXPR_P 0
#else
#    define BO_MUL_U64_IMPL(x, y) prod = bo_ptbl_mul_u64((x), (y))
#    define BO_MUL_U64_CEXPR_P BO_PTBL_CEXPR_P
#endif

BO_INTRIN_API(BO_MUL_U64_CEXPR_P)
bo_u128
bo_mul_u64(uint64_t x, uint64_t y) BO_noexcept
{
    bo_u128 prod = { 0, 0 };
    BO_MUL_U64_IMPL(x, y);
    return prod;
}

#if hu_has_builtin(__builtin_rotateleft8)
#    define BO_ROL_U8_IMPL(x, n)                                               \
        return __builtin_rotateleft8(x, bo_ucast(8, n & 7))
#    define BO_ROL_U8_CEXPR_P 0
#else
#    define BO_ROL_U8_IMPL(x, n) return bo_ptbl_rol_u8(x, n)
#    define BO_ROL_U8_CEXPR_P BO_PTBL_CEXPR_P
#endif

BO_INTRIN_API(BO_ROL_U8_CEXPR_P)
uint8_t
bo_rol_u8(uint8_t x, int n) BO_noexcept
{
    BO_ROL_U8_IMPL(x, n);
}

#if hu_has_builtin(__builtin_rotateleft16)
#    define BO_ROL_U16_IMPL(x, n)                                              \
        return __builtin_rotateleft16(x, bo_ucast(8, n & 15))
#    define BO_ROL_U16_CEXPR_P 0
#else
#    define BO_ROL_U16_IMPL(x, n) return bo_ptbl_rol_u16(x, n)
#    define BO_ROL_U16_CEXPR_P BO_PTBL_CEXPR_P
#endif

BO_INTRIN_API(BO_ROL_U16_CEXPR_P)
uint16_t
bo_rol_u16(uint16_t x, int n) BO_noexcept
{
    BO_ROL_U16_IMPL(x, n);
}

#if hu_has_builtin(__builtin_rotateleft32)
#    define BO_ROL_U32_IMPL(x, n)                                              \
        return __builtin_rotateleft32(x, bo_ucast(8, n & 31))
#    define BO_ROL_U32_CEXPR_P 0
#else
#    define BO_ROL_U32_IMPL(x, n) return bo_ptbl_rol_u32(x, n)
#    define BO_ROL_U32_CEXPR_P BO_PTBL_CEXPR_P
#endif

BO_INTRIN_API(BO_ROL_U32_CEXPR_P)
uint32_t
bo_rol_u32(uint32_t x, int n) BO_noexcept
{
    BO_ROL_U32_IMPL(x, n);
}

#if hu_has_builtin(__builtin_rotateleft64)
#    define BO_ROL_U64_IMPL(x, n)                                              \
        return __builtin_rotateleft64(x, bo_ucast(8, n & 63))
#    define BO_ROL_U64_CEXPR_P 0
#else
#    define BO_ROL_U64_IMPL(x, n) return bo_ptbl_rol_u64(x, n)
#    define BO_ROL_U64_CEXPR_P BO_PTBL_CEXPR_P
#endif

BO_INTRIN_API(BO_ROL_U64_CEXPR_P)
uint64_t
bo_rol_u64(uint64_t x, int n) BO_noexcept
{
    BO_ROL_U64_IMPL(x, n);
}

BO_DEF_ALL_3(BO_DEF_I_FWD_I, rol, ROL)

#if hu_has_builtin(__builtin_rotateright8)
#    define BO_ROR_U8_IMPL(x, n)                                               \
        return __builtin_rotateright8(x, bo_ucast(8, n & 7))
#    define BO_ROR_U8_CEXPR_P 0
#else
#    define BO_ROR_U8_IMPL(x, n) return bo_ptbl_ror_u8(x, n)
#    define BO_ROR_U8_CEXPR_P BO_PTBL_CEXPR_P
#endif

BO_INTRIN_API(BO_ROR_U8_CEXPR_P)
uint8_t
bo_ror_u8(uint8_t x, int n) BO_noexcept
{
    BO_ROR_U8_IMPL(x, n);
}

#if hu_has_builtin(__builtin_rotateright16)
#    define BO_ROR_U16_IMPL(x, n)                                              \
        return __builtin_rotateright16(x, bo_ucast(8, n & 15))
#    define BO_ROR_U16_CEXPR_P 0
#else
#    define BO_ROR_U16_IMPL(x, n) return bo_ptbl_ror_u16(x, n)
#    define BO_ROR_U16_CEXPR_P BO_PTBL_CEXPR_P
#endif

BO_INTRIN_API(BO_ROR_U16_CEXPR_P)
uint16_t
bo_ror_u16(uint16_t x, int n) BO_noexcept
{
    BO_ROR_U16_IMPL(x, n);
}

#if hu_has_builtin(__builtin_rotateright32)
#    define BO_ROR_U32_IMPL(x, n)                                              \
        return __builtin_rotateright32(x, bo_ucast(8, n & 31))
#    define BO_ROR_U32_CEXPR_P 0
#else
#    define BO_ROR_U32_IMPL(x, n) return bo_ptbl_ror_u32(x, n)
#    define BO_ROR_U32_CEXPR_P BO_PTBL_CEXPR_P
#endif

BO_INTRIN_API(BO_ROR_U32_CEXPR_P)
uint32_t
bo_ror_u32(uint32_t x, int n) BO_noexcept
{
    BO_ROR_U32_IMPL(x, n);
}

#if hu_has_builtin(__builtin_rotateright64)
#    define BO_ROR_U64_IMPL(x, n)                                              \
        return __builtin_rotateright64(x, bo_ucast(8, n & 63))
#    define BO_ROR_U64_CEXPR_P 0
#else
#    define BO_ROR_U64_IMPL(x, n) return bo_ptbl_ror_u64(x, n)
#    define BO_ROR_U64_CEXPR_P BO_PTBL_CEXPR_P
#endif

BO_INTRIN_API(BO_ROR_U64_CEXPR_P)
uint64_t
bo_ror_u64(uint64_t x, int n) BO_noexcept
{
    BO_ROR_U64_IMPL(x, n);
}

BO_DEF_ALL_3(BO_DEF_I_FWD_I, ror, ROR)

HU_END_EXTERN_C

#endif
