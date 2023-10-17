#include <catch2/catch_test_macros.hpp>

#include "src/add.h"

TEST_CASE( "Addition of 1, and 2" ) {
    REQUIRE( add(1, 2) == 3 );
}
