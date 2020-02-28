#include "bo/c/intrin.h"
#include "bo/c/portable.h"

#include "testing.h"

int
main()
{
    rand_init();
#include "shared_tests.h"
    TEST_EXIT();
}
