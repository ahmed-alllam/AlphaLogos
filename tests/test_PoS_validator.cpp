#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>

#include "../src/logic_utils/PoS_validator.h"

TEST_CASE("Validation of the term (x+y)(x+z)") {
    REQUIRE( isValidPoS("(x+y)(x+z)") == true );
}
TEST_CASE("Validation of the term x") {
    REQUIRE( isValidPoS("x") == true );
}

TEST_CASE("Validation of the term x+y") {
    REQUIRE( isValidPoS("x+y") == false );
}

TEST_CASE("Validation of the term (x)(y+z)") {
    REQUIRE( isValidPoS("(x)(y+z)") == true );
}

TEST_CASE("Validation of the term (x+y+z)(a+b+c)") {
    REQUIRE( isValidPoS("(x+y+z)(a+b+c)") == true );
}

TEST_CASE("Validation of the term (x+y)(z)") {
    REQUIRE( isValidPoS("(x+y)(z)") == true );
}

TEST_CASE("Validation of the term (x+y)(z+w)(a+b)") {
    REQUIRE( isValidPoS("(x+y)(z+w)(a+b)") == true );
}

TEST_CASE("Validation of the term (x+y+z)(x+y)") {
    REQUIRE( isValidPoS("(x+y+z)(x+y)") == true );
}

TEST_CASE("Validation of the term x+y+z") {
    REQUIRE( isValidPoS("x+y+z") == false );
}

TEST_CASE("Validation of the term x*(y+z)") {
    REQUIRE( isValidPoS("x*(y+z)") == true );
}

TEST_CASE("Validation of the term (x+y)*(z+w)*(a+b)*(c+d)") {
    REQUIRE( isValidPoS("(x+y)*(z+w)*(a+b)*(c+d)") == true );
}

TEST_CASE("Validation of the term (x+y)(z+w)(a+b)c") {
    REQUIRE( isValidPoS("(x+y)(z+w)(a+b)c") == true );
}
TEST_CASE("Validation of the term (x+y')(x'+z)") {
    REQUIRE( isValidPoS("(x+y')(x'+z)") == true );
}

TEST_CASE("Validation of the term (x'+y)(x+z')") {
    REQUIRE( isValidPoS("(x'+y)(x+z')") == true );
}

TEST_CASE("Validation of the term (x+y+z')(a'+b+c)") {
    REQUIRE( isValidPoS("(x+y+z')(a'+b+c)") == true );
}

TEST_CASE("Validation of the term (x'+y'+z)(a+b'+c')") {
    REQUIRE( isValidPoS("(x'+y'+z)(a+b'+c')") == true );
}

TEST_CASE("Validation of the term (x+y')(z'+w)(a'+b)") {
    REQUIRE( isValidPoS("(x+y')(z'+w)(a'+b)") == true );
}

TEST_CASE("Validation of the term (x+y'+z)(x'+y)") {
    REQUIRE( isValidPoS("(x+y'+z)(x'+y)") == true );
}

TEST_CASE("Validation of the term (x'+y+z')(x+y')") {
    REQUIRE( isValidPoS("(x'+y+z')(x+y')") == true );
}

TEST_CASE("Validation of the term (x+y')(z+w')(a+b')") {
    REQUIRE( isValidPoS("(x+y')(z+w')(a+b')") == true );
}

TEST_CASE("Validation of the term (x'+y')(z'+w)(a'+b')") {
    REQUIRE( isValidPoS("(x'+y')(z'+w)(a'+b')") == true );
}

TEST_CASE("Validation of the term (x+y)(x'+y')") {
    REQUIRE( isValidPoS("(x+y)(x'+y')") == true );
}

TEST_CASE("Validation of the term (x'+y')(z+w')") {
    REQUIRE( isValidPoS("(x'+y')(z+w')") == true );
}

TEST_CASE("Validation of the term x+y'+z") {
    REQUIRE( isValidPoS("x+y'+z") == false );
}

TEST_CASE("Validation of the term x'(y+z)") {
    REQUIRE( isValidPoS("x'(y+z)") == false );
}

TEST_CASE("Validation of the term (x+y')*(z'+w')*(a+b)*(c'+d)") {
    REQUIRE( isValidPoS("(x+y')*(z'+w')*(a+b)*(c'+d)") == true );
}
TEST_CASE("Validation of the term (x+y')(z+w')(a+b)c'") {
    REQUIRE( isValidPoS("(x+y')(z+w')(a+b)c'") == false );
}

TEST_CASE("Validation of the term x+y'z+w'") {
    REQUIRE( isValidPoS("x+y'z+w'") == false );
}

TEST_CASE("Validation of the term (x+y')*z+w'") {
    REQUIRE( isValidPoS("(x+y')*z+w'") == false );
}

TEST_CASE("Validation of the term (x+y')+(z+w')") {
    REQUIRE( isValidPoS("(x+y')+(z+w')") == false );
}

TEST_CASE("Validation of the term (x+y')(z+w')(a+b)+c'") {
    REQUIRE( isValidPoS("(x+y')(z+w')(a+b)+c'") == false );
}

TEST_CASE("Validation of the term (x+y')(z+w')(a+b)") {
    REQUIRE( isValidPoS("(x+y')(z+w')(a+b)") == true );
}
TEST_CASE("Validation of the term (a+b)(c+d')e+f'") {
    REQUIRE( isValidPoS("(a+b)(c+d')e+f'") == false );
}

TEST_CASE("Validation of the term (m+n')+(o+p')") {
    REQUIRE( isValidPoS("(m+n')+(o+p')") == false );
}

TEST_CASE("Validation of the term (r+s')(t+u')") {
    REQUIRE( isValidPoS("(r+s')(t+u')") == true );
}

TEST_CASE("Validation of the term (x+y')(z+w')*a'") {
    REQUIRE( isValidPoS("(x+y')(z+w')*a'") == false );
}

TEST_CASE("Validation of the term (i+j')(k+l')+(m+n')") {
    REQUIRE( isValidPoS("(i+j')(k+l')+(m+n')") == false );
}

TEST_CASE("Validation of the term a'+b'c+d'") {
    REQUIRE( isValidPoS("a'+b'c+d'") == false );
}

TEST_CASE("Validation of the term (a+b)(c+d')(e+f')") {
    REQUIRE( isValidPoS("(a+b)(c+d')(e+f')") == true );
}

TEST_CASE("Validation of the term a+b(c+d')") {
    REQUIRE( isValidPoS("a+b(c+d')") == false );
}
TEST_CASE("Validation of the term (p+q)+(r+s')(t+u')") {
    REQUIRE( isValidPoS("(p+q)+(r+s')(t+u')") == false );
}

TEST_CASE("Validation of the term (v+w')x'") {
    REQUIRE( isValidPoS("(v+w')x'") == false );
}

TEST_CASE("Validation of the term (a+b')(c+d)(e+f')+g'") {
    REQUIRE( isValidPoS("(a+b')(c+d)(e+f')+g'") == false );
}

TEST_CASE("Validation of the term (h+i')(j+k)l'") {
    REQUIRE( isValidPoS("(h+i')(j+k)l'") == false );
}

TEST_CASE("Validation of the term (m+n)o'+(p+q)"){
    REQUIRE( isValidPoS("(m+n)o'+(p+q)") == false );
}

TEST_CASE("Validation of the term (r+s')(t+u)(v+w')+x'"){
    REQUIRE( isValidPoS("(r+s')(t+u)(v+w')+x'") == false );
}

TEST_CASE("Validation of the term y+z(a+b)"){
    REQUIRE( isValidPoS("y+z(a+b)") == false );
}

TEST_CASE("Validation of the term (c+d')+(e+f')g'"){
    REQUIRE( isValidPoS("(c+d')+(e+f')g'") == false );
}
TEST_CASE("Validation of the term hamada"){
    REQUIRE( isValidPoS("hamada") == true );
}
TEST_CASE("Validation of the term xyz50"){
    REQUIRE( isValidPoS("xyz50") == false );
    }
