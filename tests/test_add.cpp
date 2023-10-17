#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>

#include "../src/logic_utils/add.h"

TEST_CASE( "Addition of 1, and 2" ) {
    REQUIRE( add(1, 2) == 3 );
}
