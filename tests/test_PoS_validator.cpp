#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>

#include "../src/logic_utils/PoS_validator.h"   // Adjust the path accordingly

TEST_CASE("Validation of the term (x+y)(x+z)") {
    REQUIRE( isPoSExpression("(x+y)(x+z)") == true );
}
TEST_CASE("Validation of the term x") {
    REQUIRE( isPoSExpression("x") == true );
}

TEST_CASE("Validation of the term x+y") {
    REQUIRE( isPoSExpression("x+y") == false );
}

TEST_CASE("Validation of the term (x)(y+z)") {
    REQUIRE( isPoSExpression("(x)(y+z)") == true );
}

TEST_CASE("Validation of the term (x+y+z)(a+b+c)") {
    REQUIRE( isPoSExpression("(x+y+z)(a+b+c)") == true );
}

TEST_CASE("Validation of the term (x+y)(z)") {
    REQUIRE( isPoSExpression("(x+y)(z)") == true );
}

TEST_CASE("Validation of the term (x+y)(z+w)(a+b)") {
    REQUIRE( isPoSExpression("(x+y)(z+w)(a+b)") == true );
}

TEST_CASE("Validation of the term (x+y+z)(x+y)") {
    REQUIRE( isPoSExpression("(x+y+z)(x+y)") == true );
}

TEST_CASE("Validation of the term x+y+z") {
    REQUIRE( isPoSExpression("x+y+z") == false );
}

TEST_CASE("Validation of the term x*(y+z)") {
    REQUIRE( isPoSExpression("x*(y+z)") == true );
}

TEST_CASE("Validation of the term (x+y)*(z+w)*(a+b)*(c+d)") {
    REQUIRE( isPoSExpression("(x+y)*(z+w)*(a+b)*(c+d)") == true );
}

TEST_CASE("Validation of the term (x+y)(z+w)(a+b)c") {
    REQUIRE( isPoSExpression("(x+y)(z+w)(a+b)c") == true );
}
TEST_CASE("Validation of the term (x+y')(x'+z)") {
    REQUIRE( isPoSExpression("(x+y')(x'+z)") == true );
}

TEST_CASE("Validation of the term (x'+y)(x+z')") {
    REQUIRE( isPoSExpression("(x'+y)(x+z')") == true );
}

TEST_CASE("Validation of the term (x+y+z')(a'+b+c)") {
    REQUIRE( isPoSExpression("(x+y+z')(a'+b+c)") == true );
}

TEST_CASE("Validation of the term (x'+y'+z)(a+b'+c')") {
    REQUIRE( isPoSExpression("(x'+y'+z)(a+b'+c')") == true );
}

TEST_CASE("Validation of the term (x+y')(z'+w)(a'+b)") {
    REQUIRE( isPoSExpression("(x+y')(z'+w)(a'+b)") == true );
}

TEST_CASE("Validation of the term (x+y'+z)(x'+y)") {
    REQUIRE( isPoSExpression("(x+y'+z)(x'+y)") == true );
}

TEST_CASE("Validation of the term (x'+y+z')(x+y')") {
    REQUIRE( isPoSExpression("(x'+y+z')(x+y')") == true );
}

TEST_CASE("Validation of the term (x+y')(z+w')(a+b')") {
    REQUIRE( isPoSExpression("(x+y')(z+w')(a+b')") == true );
}

TEST_CASE("Validation of the term (x'+y')(z'+w)(a'+b')") {
    REQUIRE( isPoSExpression("(x'+y')(z'+w)(a'+b')") == true );
}

TEST_CASE("Validation of the term (x+y)(x'+y')") {
    REQUIRE( isPoSExpression("(x+y)(x'+y')") == true );
}

TEST_CASE("Validation of the term (x'+y')(z+w')") {
    REQUIRE( isPoSExpression("(x'+y')(z+w')") == true );
}

TEST_CASE("Validation of the term x+y'+z") {
    REQUIRE( isPoSExpression("x+y'+z") == false );
}

TEST_CASE("Validation of the term x'(y+z)") {
    REQUIRE( isPoSExpression("x'(y+z)") == false );
}

TEST_CASE("Validation of the term (x+y')*(z'+w')*(a+b)*(c'+d)") {
    REQUIRE( isPoSExpression("(x+y')*(z'+w')*(a+b)*(c'+d)") == true );
}

TEST_CASE("Validation of the term (x+y')(z+w')(a+b)c'") {
    REQUIRE( isPoSExpression("(x+y')(z+w')(a+b)c'") == false );
}
