#ifndef BO_CXX_HPP
#define BO_CXX_HPP

#include <bo/c.h>
#include <hu/hu.h>
#include <type_traits>

namespace bo {

#if HU_SIZEOF_LONG == 4
#    define BO_ULONG_CALL(fn) BO_CAT(fn, _u32)
#elif HU_SIZEOF_LONG == 8
#    define BO_ULONG_CALL(fn) BO_CAT(fn, _u64)
#else
#    error                                                                     \
      "Excuse me madam/sir, sizeof(long) is neither 4 nor 8 bytes, what arch is this?"
#endif

#define BO_CXX_API(CEXPR_P) BO_INTRIN_API(CEXPR_P)
#define BO_CXX_API_CEXPR BO_INTRIN_API(1)

template<typename T>
struct widen_int;

template<typename T>
using widen_int_t = typename widen_int<T>::type;

template<typename T>
struct narrow_int;

template<typename T>
using narrow_int_t = typename narrow_int<T>::type;

#define BO_DEF_WIDEN_INT(T, WT)                                                \
    template<>                                                                 \
    struct widen_int<T>                                                        \
    {                                                                          \
        using type = WT;                                                       \
    }

#define BO_DEF_NARROW_INT(T, WT)                                               \
    template<>                                                                 \
    struct narrow_int<WT>                                                      \
    {                                                                          \
        using type = T;                                                        \
    }

#define BO_DEF_WIDEN_NARROW_INT(T, UT, WT, UWT)                                \
    BO_DEF_WIDEN_INT(T, WT);                                                   \
    BO_DEF_WIDEN_INT(UT, UWT);                                                 \
    BO_DEF_NARROW_INT(T, WT);                                                  \
    BO_DEF_NARROW_INT(UT, UWT)

BO_DEF_WIDEN_NARROW_INT(int8_t, uint8_t, int16_t, uint16_t);
BO_DEF_WIDEN_NARROW_INT(int16_t, uint16_t, int32_t, uint32_t);
BO_DEF_WIDEN_NARROW_INT(int32_t, uint32_t, int64_t, uint64_t);

#if BO_HAVE_INT128_P && HU_SIZEOF_LONG == 8
BO_DEF_WIDEN_NARROW_INT(long, unsigned long, __int128, unsigned __int128);
#endif

#if BO_HAVE_INT128_P && HU_SIZEOF_LONG_LONG == 8
BO_DEF_WIDEN_INT(long long, __int128);
BO_DEF_WIDEN_INT(unsigned long long, unsigned __int128);
#    if HU_SIZEOF_LONG < 8
BO_DEF_NARROW_INT(long long, __int128);
BO_DEF_NARROW_INT(unsigned long long, unsigned __int128);
#    endif
#endif

template<typename T>
BO_CXX_API_CEXPR widen_int_t<T>
widen(T x) noexcept
{
    return x;
}

BO_CXX_API(BO_POPCNT_U8_CEXPR_P)
int
popcnt(unsigned char x) noexcept
{
    return bo_popcnt_u8(x);
}

BO_CXX_API(BO_POPCNT_U8_CEXPR_P)
int
popcnt(char x) noexcept
{
    return bo_popcnt_u8(uint8_t(x));
}

BO_CXX_API(BO_POPCNT_U16_CEXPR_P)
int
popcnt(unsigned short x) noexcept
{
    return bo_popcnt_u16(x);
}

BO_CXX_API(BO_POPCNT_U32_CEXPR_P)
int
popcnt(unsigned int x) noexcept
{
    return bo_popcnt_u32(x);
}

BO_CXX_API(BO_POPCNT_U64_CEXPR_P)
int
popcnt(unsigned long x) noexcept
{
    return BO_ULONG_CALL(bo_popcnt)(x);
}

BO_CXX_API(BO_POPCNT_U64_CEXPR_P)
int
popcnt(unsigned long long x) noexcept
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

BO_CXX_API(BO_BSWAP_U16_CEXPR_P)
unsigned short
bswap(unsigned short x) noexcept
{
    return bo_bswap_u16(x);
}

BO_CXX_API(BO_BSWAP_U32_CEXPR_P)
unsigned int
bswap(unsigned int x) noexcept
{
    return bo_bswap_u32(x);
}

BO_CXX_API(BO_BSWAP_U64_CEXPR_P)
unsigned long
bswap(unsigned long x) noexcept
{
    return BO_ULONG_CALL(bo_bswap)(x);
}

BO_CXX_API(BO_BSWAP_U64_CEXPR_P)
unsigned long long
bswap(unsigned long long x) noexcept
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

BO_CXX_API(BO_REV_U8_CEXPR_P)
unsigned char
rev(unsigned char x) noexcept
{
    return bo_rev_u8(x);
}

BO_CXX_API(BO_REV_U8_CEXPR_P)
char
rev(char x) noexcept
{
    return char(bo_rev_u8(uint8_t(x)));
}

BO_CXX_API(BO_REV_U16_CEXPR_P)
unsigned short
rev(unsigned short x) noexcept
{
    return bo_rev_u16(x);
}

BO_CXX_API(BO_REV_U32_CEXPR_P)
unsigned int
rev(unsigned int x) noexcept
{
    return bo_rev_u32(x);
}

BO_CXX_API(BO_REV_U64_CEXPR_P)
unsigned long
rev(unsigned long x) noexcept
{
    return BO_ULONG_CALL(bo_rev)(x);
}

BO_CXX_API(BO_REV_U64_CEXPR_P)
unsigned long long
rev(unsigned long long x) noexcept
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

BO_CXX_API(BO_CTZ_U8_CEXPR_P)
int
ctz(unsigned char x) noexcept
{
    return bo_ctz_u8(x);
}

BO_CXX_API(BO_CTZ_U8_CEXPR_P)
int
ctz(char x) noexcept
{
    return bo_ctz_u8(uint8_t(x));
}

BO_CXX_API(BO_CTZ_U16_CEXPR_P)
int
ctz(unsigned short x) noexcept
{
    return bo_ctz_u16(x);
}

BO_CXX_API(BO_CTZ_U32_CEXPR_P)
int
ctz(unsigned int x) noexcept
{
    return bo_ctz_u32(x);
}

BO_CXX_API(BO_CTZ_U64_CEXPR_P)
int
ctz(unsigned long x) noexcept
{
    return BO_ULONG_CALL(bo_ctz)(x);
}

BO_CXX_API(BO_CTZ_U64_CEXPR_P)
int
ctz(unsigned long long x) noexcept
{
    return bo_ctz_u64(x);
}

template<typename T>
constexpr typename std::enable_if<std::is_signed<T>::value, int>::type
ctz(const T &x) noexcept
{
    return ctz(static_cast<typename std::make_unsigned<T>::type>(x));
}

BO_CXX_API(BO_CLZ_U8_CEXPR_P)
int
clz(unsigned char x) noexcept
{
    return bo_clz_u8(x);
}

BO_CXX_API(BO_CLZ_U8_CEXPR_P)
int
clz(char x) noexcept
{
    return bo_clz_u8(uint8_t(x));
}

BO_CXX_API(BO_CLZ_U16_CEXPR_P)
int
clz(unsigned short x) noexcept
{
    return bo_clz_u16(x);
}

BO_CXX_API(BO_CLZ_U32_CEXPR_P)
int
clz(unsigned int x) noexcept
{
    return bo_clz_u32(x);
}

BO_CXX_API(BO_CLZ_U64_CEXPR_P)
int
clz(unsigned long x) noexcept
{
    return BO_ULONG_CALL(bo_clz)(x);
}

BO_CXX_API(BO_CLZ_U64_CEXPR_P)
int
clz(unsigned long long x) noexcept
{
    return bo_clz_u64(x);
}

template<typename T>
constexpr typename std::enable_if<std::is_signed<T>::value, int>::type
clz(const T &x) noexcept
{
    return clz(static_cast<typename std::make_unsigned<T>::type>(x));
}

BO_CXX_API(BO_PARITY_U8_CEXPR_P)
bool
parity(unsigned char x) noexcept
{
    return bo_parity_u8(x);
}

BO_CXX_API(BO_PARITY_U8_CEXPR_P)
bool
parity(char x) noexcept
{
    return bo_parity_u8(uint8_t(x));
}

BO_CXX_API(BO_PARITY_U16_CEXPR_P)
bool
parity(unsigned short x) noexcept
{
    return bo_parity_u16(x);
}

BO_CXX_API(BO_PARITY_U32_CEXPR_P)
bool
parity(unsigned int x) noexcept
{
    return bo_parity_u32(x);
}

BO_CXX_API(BO_PARITY_U64_CEXPR_P)
bool
parity(unsigned long x) noexcept
{
    return BO_ULONG_CALL(bo_parity)(x);
}

BO_CXX_API(BO_PARITY_U64_CEXPR_P)
bool
parity(unsigned long long x) noexcept
{
    return bo_parity_u64(x);
}

template<typename T>
constexpr typename std::enable_if<std::is_signed<T>::value, bool>::type
parity(const T &x) noexcept
{
    return parity(static_cast<typename std::make_unsigned<T>::type>(x));
}

BO_CXX_API(BO_ROL_U8_CEXPR_P)
unsigned char
rol(unsigned char x, int n) noexcept
{
    return bo_rol_u8(x, n);
}

BO_CXX_API(BO_ROL_U8_CEXPR_P)
char
rol(char x, int n) noexcept
{
    return static_cast<char>(bo_rol_u8(static_cast<unsigned char>(x), n));
}

BO_CXX_API(BO_ROL_U16_CEXPR_P)
unsigned short
rol(unsigned short x, int n) noexcept
{
    return bo_rol_u16(x, n);
}

BO_CXX_API(BO_ROL_U32_CEXPR_P)
unsigned int
rol(unsigned int x, int n) noexcept
{
    return bo_rol_u32(x, n);
}

BO_CXX_API(BO_ROL_U64_CEXPR_P)
unsigned long
rol(unsigned long x, int n) noexcept
{
    return BO_ULONG_CALL(bo_rol)(x, n);
}

BO_CXX_API(BO_ROL_U64_CEXPR_P)
unsigned long long
rol(unsigned long long x, int n) noexcept
{
    return bo_rol_u64(x, n);
}

template<typename T>
constexpr typename std::enable_if<std::is_signed<T>::value, int>::type
rol(const T &x, int n) noexcept
{
    return rol(static_cast<typename std::make_unsigned<T>::type>(x), n);
}

BO_CXX_API(BO_ROR_U8_CEXPR_P)
unsigned char
ror(unsigned char x, int n) noexcept
{
    return bo_ror_u8(x, n);
}

BO_CXX_API(BO_ROR_U8_CEXPR_P)
char
ror(char x, int n) noexcept
{
    return static_cast<char>(bo_ror_u8(static_cast<unsigned char>(x), n));
}

BO_CXX_API(BO_ROR_U16_CEXPR_P)
unsigned short
ror(unsigned short x, int n) noexcept
{
    return bo_ror_u16(x, n);
}

BO_CXX_API(BO_ROR_U32_CEXPR_P)
unsigned int
ror(unsigned int x, int n) noexcept
{
    return bo_ror_u32(x, n);
}

BO_CXX_API(BO_ROR_U64_CEXPR_P)
unsigned long
ror(unsigned long x, int n) noexcept
{
    return BO_ULONG_CALL(bo_ror)(x, n);
}

BO_CXX_API(BO_ROR_U64_CEXPR_P)
unsigned long long
ror(unsigned long long x, int n) noexcept
{
    return bo_ror_u64(x, n);
}

template<typename T>
constexpr typename std::enable_if<std::is_signed<T>::value, int>::type
ror(const T &x, int n) noexcept
{
    return ror(static_cast<typename std::make_unsigned<T>::type>(x), n);
}

} // namespace bo

#endif
