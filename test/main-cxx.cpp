#include <bo/cxx.hpp>

#include "testing.h"

int
main()
{
    TEST_GROUP("c++api")
    {
        TEST("popcnt") { equal(bo::popcnt(uint8_t(42)), 3); }
    }

    TEST_EXIT();
}
