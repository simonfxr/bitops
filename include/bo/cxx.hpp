#ifndef BO_CXX_HPP
#define BO_CXX_HPP

#include <bo/c.h>
#include <type_traits>

namespace bo {

#define BO_ULONG_BITS 64
#define BO_ULONG_CALL(fn) BO_CAT(BO_CAT(fn, _u), BO_ULONG_BITS)

BO_INTRIN_API(BO_POPCNT_U8_CEXPR_P)
int
popcnt(unsigned char x)
{
    return bo_popcnt_u8(x);
}

BO_INTRIN_API(BO_POPCNT_U8_CEXPR_P)
int
popcnt(char x)
{
    return bo_popcnt_u8(uint8_t(x));
}

BO_INTRIN_API(BO_POPCNT_U16_CEXPR_P)
int
popcnt(unsigned short x)
{
    return bo_popcnt_u16(x);
}

BO_INTRIN_API(BO_POPCNT_U32_CEXPR_P)
int
popcnt(unsigned int x)
{
    return bo_popcnt_u32(x);
}

BO_INTRIN_API(BO_POPCNT_U64_CEXPR_P)
int
popcnt(unsigned long x){ return BO_ULONG_CALL(bo_popcnt)(x) }

BO_INTRIN_API(BO_POPCNT_U64_CEXPR_P) int popcnt(unsigned long long x)
{
    return bo_popcnt_u64(x);
}

BO_PTBL_API
unsigned char
bswap(unsigned char x)
{
    return x;
}

BO_PTBL_API
char
bswap(char x)
{
    return x;
}

BO_INTRIN_API(BO_BSWAP_U16_CEXPR_P)
unsigned short
bswap(unsigned short x)
{
    return bo_bswap_u16(x);
}

BO_INTRIN_API(BO_BSWAP_U32_CEXPR_P)
unsigned int
bswap(unsigned int x)
{
    return bo_bswap_u32(x);
}

BO_INTRIN_API(BO_BSWAP_U64_CEXPR_P)
unsigned long
bswap(unsigned long x){ return BO_ULONG_CALL(bo_bswap)(x) }

BO_INTRIN_API(BO_BSWAP_U64_CEXPR_P) unsigned long long bswap(
  unsigned long long x)
{
    return bo_bswap_u64(x);
}

BO_INTRIN_API(BO_REV_U8_CEXPR_P)
unsigned char
rev(unsigned char x)
{
    return bo_rev_u8(x);
}

BO_INTRIN_API(BO_REV_U8_CEXPR_P)
char
rev(char x)
{
    return char(bo_rev_u8(uint8_t(x)));
}

BO_INTRIN_API(BO_REV_U16_CEXPR_P)
unsigned short
rev(unsigned short x)
{
    return bo_rev_u16(x);
}

BO_INTRIN_API(BO_REV_U32_CEXPR_P)
unsigned int
rev(unsigned int x)
{
    return bo_rev_u32(x);
}

BO_INTRIN_API(BO_REV_U64_CEXPR_P)
unsigned long
rev(unsigned long x){ return BO_ULONG_CALL(bo_rev)(x) }

BO_INTRIN_API(BO_REV_U64_CEXPR_P) unsigned long long rev(unsigned long long x)
{
    return bo_rev_u64(x);
}

} // namespace bo

#endif
