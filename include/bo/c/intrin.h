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

#define BO_cexpr_if(P) BO_CAT(BO_cexpr_if_, P)

#define BO_cexpr_if_0
#define BO_cexpr_if_1 BO_cexpr

#define BO_INTRIN_API(CEXPR_P) BO_cexpr_if(CEXPR_P)

#if HU_ARCH_X86_P && hu_has_include(<x86intrin.h>)
#    include <x86intrin.h>
#    define BO_HAVE_X86_INTRIN_H_P 1
#else
#    define BO_HAVE_X86_INTRIN_H_P 0
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
bo_popcnt_u32(uint32_t x)
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
#    define BO_POPCNT_U16_IMPL(x) BO_POPCNT_U32_IMPL((uint32_t) x)
#    define BO_POPCNT_U16_CEXPR_P BO_POPCNT_U32_CEXPR_P
#    define BO_HAVE_POPCNT_U16_INTRIN_P() 1
#else
#    define BO_POPCNT_U16_IMPL bo_ptbl_popcnt_u16
#    define BO_POPCNT_U16_CEXPR_P 1
#    define BO_HAVE_POPCNT_U16_INTRIN_P() 0
#endif

BO_INTRIN_API(BO_POPCNT_U16_CEXPR_P)
int
bo_popcnt_u16(uint16_t x)
{
    return BO_POPCNT_U16_IMPL(x);
}

#if BO_HAVE_CXX_BIT_H_P()
#    define BO_POPCNT_U8_IMPL std::popcount
#    define BO_POPCNT_U8_CEXPR_P 1
#elif BO_HAVE_POPCNT_U16_INTRIN_P()
#    define BO_POPCNT_U8_IMPL(x) BO_POPCNT_U16_IMPL((uint32_t) x)
#    define BO_POPCNT_U8_CEXPR_P BO_POPCNT_U16_CEXPR_P
#else
#    define BO_POPCNT_U8_IMPL bo_ptbl_popcnt_u8
#    define BO_POPCNT_U8_CEXPR_P 1
#endif

BO_INTRIN_API(BO_POPCNT_U8_CEXPR_P)
int
bo_popcnt_u8(uint8_t x)
{
    return BO_POPCNT_U8_IMPL(x);
}

#if BO_HAVE_CXX_BIT_H_P()
#    define BO_POPCNT_U64_IMPL std::popcount
#    define BO_POPCNT_U64_CEXPR_P 1
#elif hu_has_builtin(__builtin_popcountll) || HU_COMP_GNUC_P
#    define BO_POPCNT_U64_IMPL(x)                                              \
        (int) __builtin_popcountll((unsigned long long) x)
#    define BO_POPCNT_U64_CEXPR_P 1
#elif BO_HAVE_MSVC_INTRIN_H_P() && HU_ARCH_X86_P && HU_BITS_64_P
#    define BO_POPCNT_U64_IMPL(x) (int) __popcnt64(x)
#    define BO_POPCNT_U64_CEXPR_P 1
#elif BO_HAVE_POPCNT_U32_INTRIN_P()
#    define BO_POPCNT_U64_IMPL(x)                                              \
        BO_POPCNT_U32_IMPL((uint32_t) x) +                                     \
          BO_POPCNT_U32_IMPL((uint32_t)(x >> 32))
#    define BO_POPCNT_U64_CEXPR_P BO_POPCNT_U32_CEXPR_P
#else
#    define BO_POPCNT_U64_IMPL bo_ptbl_popcnt_u64
#    define BO_POPCNT_U64_CEXPR_P BO_PTBL_CEXPR_P
#endif

BO_INTRIN_API(BO_POPCNT_U64_CEXPR_P)
int
bo_popcnt_u64(uint64_t x)
{
    return BO_POPCNT_U64_IMPL(x);
}

BO_PTBL_API
uint8_t
bo_bswap_u8(uint8_t x)
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
bo_bswap_u16(uint16_t x)
{
    return BO_BSWAP_U16_IMPL(x);
}

#if hu_has_builtin(__builtin_bswap32) || HU_COMP_GNUC_P
#    define BO_BSWAP_U32_IMPL __builtin_bswap32
#    define BO_BSWAP_U32_CEXPR_P 1
#elif HU_COMP_MSVC_P
#    define BO_BSWAP_U32_IMPL(x) (uint32_t) _byteswap_ulong((unsigned long) x)
#    define BO_BSWAP_U32_CEXPR_P 1
#else
#    define BO_BSWAP_U32_IMPL bo_ptbl_bswap_u32
#    define BO_BSWAP_U32_CEXPR_P BO_PTBL_CEXPR_P
#endif

BO_INTRIN_API(BO_BSWAP_U32_CEXPR_P)
uint32_t
bo_bswap_u32(uint32_t x)
{
    return BO_BSWAP_U32_IMPL(x);
}

#if hu_has_builtin(__builtin_bswap64) || HU_COMP_GNUC_P
#    define BO_BSWAP_U64_IMPL __builtin_bswap64
#    define BO_BSWAP_U64_CEXPR_P 1
#elif HU_COMP_MSVC_P
#    define BO_BSWAP_U64_IMPL(x)                                               \
        (uint64_t) _byteswap_uint64((unsigned __int64) x)
#    define BO_BSWAP_U64_CEXPR_P 1
#else
#    define BO_BSWAP_U64_IMPL bo_ptbl_bswap_u64
#    define BO_BSWAP_U64_CEXPR_P BO_PTBL_CEXPR_P
#endif

BO_INTRIN_API(BO_BSWAP_U64_CEXPR_P)
uint64_t
bo_bswap_u64(uint64_t x)
{
    return BO_BSWAP_U64_IMPL(x);
}

#if hu_has_builtin(__builtin_bitreverse8)
#    define BO_REV_U8_IMPL(x) return __builtin_bitreverse8(x);
#    define BO_REV_U8_CEXPR_P 1
#else
#    define BO_REV_U8_IMPL(x) return bo_ptbl_rev_u8(x);
#    define BO_REV_U8_CEXPR_P BO_PTBL_CEXPR_P
#endif

BO_INTRIN_API(BO_REV_U8_CEXPR_P)
uint8_t
bo_rev_u8(uint8_t x)
{
    BO_REV_U8_IMPL(x)
}

#if hu_has_builtin(__builtin_bitreverse16)
#    define BO_REV_U16_IMPL(x) return __builtin_bitreverse16(x);
#    define BO_REV_U16_CEXPR_P 1
#else
#    define BO_REV_U16_IMPL(x)                                                 \
        x = ((x & 0x5555) << 1) | ((x >> 1) & 0x5555);                         \
        x = ((x & 0x3333) << 2) | ((x >> 2) & 0x3333);                         \
        x = ((x & 0x0F0F) << 4) | ((x >> 4) & 0x0F0F);                         \
        return bo_bswap_u16(x);
#    define BO_REV_U16_CEXPR_P BO_PTBL_CEXPR_P
#endif

BO_INTRIN_API(BO_REV_U16_CEXPR_P)
uint16_t
bo_rev_u16(uint16_t x)
{
    BO_REV_U16_IMPL(x)
}

#if hu_has_builtin(__builtin_bitreverse32)
#    define BO_REV_U32_IMPL(x) return __builtin_bitreverse32(x);
#    define BO_REV_U32_CEXPR_P 1
#else
#    define BO_REV_U32_IMPL(x)                                                 \
        x = ((x & 0x55555555) << 1) | ((x >> 1) & 0x55555555);                 \
        x = ((x & 0x33333333) << 2) | ((x >> 2) & 0x33333333);                 \
        x = ((x & 0x0F0F0F0F) << 4) | ((x >> 4) & 0x0F0F0F0F);                 \
        return bo_bswap_u32(x);
#    define BO_REV_U32_CEXPR_P BO_PTBL_CEXPR_P
#endif

BO_INTRIN_API(BO_REV_U32_CEXPR_P)
uint32_t
bo_rev_u32(uint32_t x)
{
    BO_REV_U32_IMPL(x)
}

#if hu_has_builtin(__builtin_bitreverse64)
#    define BO_REV_U64_IMPL(x) return __builtin_bitreverse64(x);
#    define BO_REV_U64_CEXPR_P 1
#else
#    define BO_REV_U64_IMPL(x)                                                 \
        x = ((x & 0x5555555555555555) << 1) | ((x >> 1) & 0x5555555555555555); \
        x = ((x & 0x3333333333333333) << 2) | ((x >> 2) & 0x3333333333333333); \
        x = ((x & 0x0F0F0F0F0F0F0F0F) << 4) | ((x >> 4) & 0x0F0F0F0F0F0F0F0F); \
        return bo_bswap_u64(x);
#    define BO_REV_U64_CEXPR_P BO_PTBL_CEXPR_P
#endif

BO_INTRIN_API(BO_REV_U64_CEXPR_P)
uint64_t
bo_rev_u64(uint64_t x)
{
    BO_REV_U64_IMPL(x)
}

#endif
