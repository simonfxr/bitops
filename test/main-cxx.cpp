#include <bo/cxx.hpp>

#include "testing.h"

int
main()
{
    rand_init();

#include "shared_tests.h"

    TEST_GROUP("c++api")
    {
        TEST("popcnt") { equal(bo::popcnt(uint8_t(42)), 3); }
    }

    TEST_EXIT();
}
