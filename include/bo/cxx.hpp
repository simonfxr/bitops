#ifndef BO_CXX_HPP
#define BO_CXX_HPP

#include <bo/c.h>
#include <hu.h>
#include <type_traits>

namespace bo {

#if HU_SIZEOF_LONG == 4
#    define BO_ULONG_CALL(fn) BO_CAT(fn, _u32)
#else
#    define BO_ULONG_CALL(fn) BO_CAT(fn, _u64)
#endif

typedef unsigned long long bo_ull_t;

BO_INTRIN_API(BO_POPCNT_U8_CEXPR_P)
int
popcnt(unsigned char x) noexcept
{
    return bo_popcnt_u8(x);
}

BO_INTRIN_API(BO_POPCNT_U8_CEXPR_P)
int
popcnt(char x) noexcept
{
    return bo_popcnt_u8(uint8_t(x));
}

BO_INTRIN_API(BO_POPCNT_U16_CEXPR_P)
int
popcnt(unsigned short x) noexcept
{
    return bo_popcnt_u16(x);
}

BO_INTRIN_API(BO_POPCNT_U32_CEXPR_P)
int
popcnt(unsigned int x) noexcept
{
    return bo_popcnt_u32(x);
}

BO_INTRIN_API(BO_POPCNT_U64_CEXPR_P)
int
popcnt(unsigned long x) noexcept
{
    return BO_ULONG_CALL(bo_popcnt)(x);
}

BO_INTRIN_API(BO_POPCNT_U64_CEXPR_P)
int
popcnt(bo_ull_t x) noexcept
{
    return bo_popcnt_u64(x);
}

template<typename T>
constexpr typename std::enable_if<std::is_signed<T>::value, int>::type
popcnt(const T &x) noexcept
{
    return popcnt(static_cast<typename std::make_unsigned<T>::type>(x));
}

BO_PTBL_API
unsigned char
bswap(unsigned char x) noexcept
{
    return x;
}

BO_PTBL_API
char
bswap(char x) noexcept
{
    return x;
}

BO_INTRIN_API(BO_BSWAP_U16_CEXPR_P)
unsigned short
bswap(unsigned short x) noexcept
{
    return bo_bswap_u16(x);
}

BO_INTRIN_API(BO_BSWAP_U32_CEXPR_P)
unsigned int
bswap(unsigned int x) noexcept
{
    return bo_bswap_u32(x);
}

BO_INTRIN_API(BO_BSWAP_U64_CEXPR_P)
unsigned long
bswap(unsigned long x) noexcept
{
    return BO_ULONG_CALL(bo_bswap)(x);
}

BO_INTRIN_API(BO_BSWAP_U64_CEXPR_P)
bo_ull_t
bswap(bo_ull_t x) noexcept
{
    return bo_bswap_u64(x);
}

template<typename T>
constexpr typename std::enable_if<std::is_signed<T>::value, int>::type
bswap(const T &x) noexcept
{
    return static_cast<T>(
      bswap(static_cast<typename std::make_unsigned<T>::type>(x)));
}

BO_INTRIN_API(BO_REV_U8_CEXPR_P)
unsigned char
rev(unsigned char x) noexcept
{
    return bo_rev_u8(x);
}

BO_INTRIN_API(BO_REV_U8_CEXPR_P)
char
rev(char x) noexcept
{
    return char(bo_rev_u8(uint8_t(x)));
}

BO_INTRIN_API(BO_REV_U16_CEXPR_P)
unsigned short
rev(unsigned short x) noexcept
{
    return bo_rev_u16(x);
}

BO_INTRIN_API(BO_REV_U32_CEXPR_P)
unsigned int
rev(unsigned int x) noexcept
{
    return bo_rev_u32(x);
}

BO_INTRIN_API(BO_REV_U64_CEXPR_P)
unsigned long
rev(unsigned long x) noexcept
{
    return BO_ULONG_CALL(bo_rev)(x);
}

BO_INTRIN_API(BO_REV_U64_CEXPR_P)
bo_ull_t
rev(bo_ull_t x) noexcept
{
    return bo_rev_u64(x);
}

template<typename T>
constexpr typename std::enable_if<std::is_signed<T>::value, int>::type
rev(const T &x) noexcept
{
    return static_cast<T>(
      rev(static_cast<typename std::make_unsigned<T>::type>(x)));
}

BO_INTRIN_API(BO_CTZ_U8_CEXPR_P)
int
ctz(unsigned char x) noexcept
{
    return bo_ctz_u8(x);
}

BO_INTRIN_API(BO_CTZ_U8_CEXPR_P)
int
ctz(char x) noexcept
{
    return bo_ctz_u8(uint8_t(x));
}

BO_INTRIN_API(BO_CTZ_U16_CEXPR_P)
int
ctz(unsigned short x) noexcept
{
    return bo_ctz_u16(x);
}

BO_INTRIN_API(BO_CTZ_U32_CEXPR_P)
int
ctz(unsigned int x) noexcept
{
    return bo_ctz_u32(x);
}

BO_INTRIN_API(BO_CTZ_U64_CEXPR_P)
int
ctz(unsigned long x) noexcept
{
    return BO_ULONG_CALL(bo_ctz)(x);
}

BO_INTRIN_API(BO_CTZ_U64_CEXPR_P)
int
ctz(bo_ull_t x) noexcept
{
    return bo_ctz_u64(x);
}

template<typename T>
constexpr typename std::enable_if<std::is_signed<T>::value, int>::type
ctz(const T &x) noexcept
{
    return ctz(static_cast<typename std::make_unsigned<T>::type>(x));
}

BO_INTRIN_API(BO_CLZ_U8_CEXPR_P)
int
clz(unsigned char x) noexcept
{
    return bo_clz_u8(x);
}

BO_INTRIN_API(BO_CLZ_U8_CEXPR_P)
int
clz(char x) noexcept
{
    return bo_clz_u8(uint8_t(x));
}

BO_INTRIN_API(BO_CLZ_U16_CEXPR_P)
int
clz(unsigned short x) noexcept
{
    return bo_clz_u16(x);
}

BO_INTRIN_API(BO_CLZ_U32_CEXPR_P)
int
clz(unsigned int x) noexcept
{
    return bo_clz_u32(x);
}

BO_INTRIN_API(BO_CLZ_U64_CEXPR_P)
int
clz(unsigned long x) noexcept
{
    return BO_ULONG_CALL(bo_clz)(x);
}

BO_INTRIN_API(BO_CLZ_U64_CEXPR_P)
int
clz(bo_ull_t x) noexcept
{
    return bo_clz_u64(x);
}

template<typename T>
constexpr typename std::enable_if<std::is_signed<T>::value, int>::type
clz(const T &x) noexcept
{
    return clz(static_cast<typename std::make_unsigned<T>::type>(x));
}

BO_INTRIN_API(BO_PARITY_U8_CEXPR_P)
bool
parity(unsigned char x) noexcept
{
    return bo_parity_u8(x);
}

BO_INTRIN_API(BO_PARITY_U8_CEXPR_P)
bool
parity(char x) noexcept
{
    return bo_parity_u8(uint8_t(x));
}

BO_INTRIN_API(BO_PARITY_U16_CEXPR_P)
bool
parity(unsigned short x) noexcept
{
    return bo_parity_u16(x);
}

BO_INTRIN_API(BO_PARITY_U32_CEXPR_P)
bool
parity(unsigned int x) noexcept
{
    return bo_parity_u32(x);
}

BO_INTRIN_API(BO_PARITY_U64_CEXPR_P)
bool
parity(unsigned long x) noexcept
{
    return BO_ULONG_CALL(bo_parity)(x);
}

BO_INTRIN_API(BO_PARITY_U64_CEXPR_P)
bool
parity(bo_ull_t x) noexcept
{
    return bo_parity_u64(x);
}

template<typename T>
constexpr typename std::enable_if<std::is_signed<T>::value, bool>::type
parity(const T &x) noexcept
{
    return parity(static_cast<typename std::make_unsigned<T>::type>(x));
}

} // namespace bo

#endif
