
#include "bo/c/intrin.h"
#include "bo/c/portable.h"

int
main()
{
    int x = bo_ptbl_popcnt_u8((uint8_t) 13);
    return x;
}
