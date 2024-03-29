#ifndef BO_TEST_RAND_H
#define BO_TEST_RAND_H

#include <stdint.h>

#include <hu/hu.h>

// The following code can be found here:
// https://www.pcg-random.org/download.html
// It has been slightly modifed to silence implicit type conversion warnings.
// The snippet extends until END PCG32
// BEGIN PCG32

// *Really* minimal PCG32 code / (c) 2014 M.E. O'Neill / pcg-random.org
// Licensed under Apache License 2.0 (NO WARRANTY, etc. see website)

typedef struct
{
    uint64_t state;
    uint64_t inc;
} pcg32_random_t;

static uint32_t
pcg32_random_r(pcg32_random_t *rng)
{
    uint64_t oldstate = rng->state;
    // Advance internal state
    rng->state = oldstate * 6364136223846793005ULL + (rng->inc | 1);
    // Calculate output function (XSH RR), uses old state for max ILP
    uint32_t xorshifted =
      hu_static_cast(uint32_t, ((oldstate >> 18u) ^ oldstate) >> 27u);
    uint32_t rot = hu_static_cast(uint32_t, oldstate >> 59u);
    return (xorshifted >> rot) | (xorshifted << ((-rot) & 31));
}

// END PCG32

static pcg32_random_t
rng_derive(uint64_t seed, uint64_t s0)
{
    pcg32_random_t fresh = { 0, 0x10070d7aebfb045bull };
    fresh.state = seed;
    fresh.state ^= (s0 << 13) | (s0 >> (64 - 13));
    return fresh;
}

static uint64_t
djb2_strhash(uint64_t h0, const char *s)
{
    uint64_t h = h0 * 5381ull;
    while (*s)
        h = ((h << 5) + h) + hu_static_cast(uint8_t, *s++);
    return h;
}

static int64_t
rng_randbits_in(pcg32_random_t *rng, unsigned n)
{
    uint64_t x = pcg32_random_r(rng);
    x <<= 32;
    if (n > 32)
        x |= pcg32_random_r(rng);
    int64_t y = hu_static_cast(int64_t, x);
    y >>= 64 - n;
    return y;
}

static uint64_t
rng_randbits_un(pcg32_random_t *rng, unsigned n)
{
    uint64_t x = pcg32_random_r(rng);
    x <<= 32;
    if (n > 32)
        x |= pcg32_random_r(rng);
    x >>= 64 - n;
    return x;
}

static uint64_t
rng_rand_un(pcg32_random_t *rng, unsigned nbits)
{
    uint32_t x = pcg32_random_r(rng);
    uint64_t ret;
    switch (x & 7) {
    case 0:
        ret = 0;
        break;
    case 1:
        ret = 1;
        break;
    case 2:
        ret = (1ull << nbits) - 1ull;
        break;
    case 3:
        ret = rng_randbits_un(rng, nbits);
        break;
    default:
        ret = rng_randbits_un(rng, (x >> 3) & (nbits - 1));
    }
    return ret;
}

static int64_t
rng_rand_in(pcg32_random_t *rng, unsigned nbits)
{
    uint32_t x = pcg32_random_r(rng);
    int64_t ret;
    switch (x & 7) {
    case 0:
        ret = 0;
        break;
    case 1:
        ret = 1;
        break;
    case 2:
        ret = -1;
        break;
    case 3:
        ret = rng_randbits_in(rng, nbits);
        break;
    default:
        ret = rng_randbits_in(rng, (x >> 3) & (nbits - 1));
    }
    return ret;
}

static const int RAND_ITER_PER_U16 = 3001;

static inline int
rand_iter_for_bits(unsigned bits)
{
    if (bits <= 8)
        return 512;
    if (bits <= 16)
        return RAND_ITER_PER_U16;
    if (bits <= 32)
        return RAND_ITER_PER_U16 * RAND_ITER_PER_U16 / 16;
    return RAND_ITER_PER_U16 * RAND_ITER_PER_U16;
}

#endif
