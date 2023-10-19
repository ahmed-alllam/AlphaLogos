#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>

#include "../src/logic_utils/SoP_validator.h"

TEST_CASE( "Validation of expression x + y") {
          REQUIRE(isSoPExpression("x + y") == true);
}
          
TEST_CASE("Valid SoP: (A*B') + (C*D)") {
    REQUIRE(isSoPExpression("(A*B') + (C*D)") == true);
}

TEST_CASE("Valid SoP: (X'*Y) + (Z*W') + (M*N)") {
    REQUIRE(isSoPExpression("(X'*Y) + (Z*W') + (M*N)") == true);
}

TEST_CASE("Valid SoP: (A*B*C')") {
    REQUIRE(isSoPExpression("(A*B*C')") == true);
}

TEST_CASE("Valid SoP: (J'*K*L) + (N*O'*P)") {
    REQUIRE(isSoPExpression("(J'*K*L) + (N*O'*P)") == true);
}

TEST_CASE("Valid SoP: (U*V') + (W*X) + (Y*Z)") {
    REQUIRE(isSoPExpression("(U*V') + (W*X) + (Y*Z)") == true);
}

TEST_CASE("Valid SoP: (G*H*I')") {
    REQUIRE(isSoPExpression("(G*H*I')") == true);
}

TEST_CASE("Valid SoP: (A+B) + (C*D)") {
    REQUIRE(isSoPExpression("(A+B) + (C*D)") == true);
}

TEST_CASE("Invalid SoP: (X'*Y) * (Z+W')") {
    REQUIRE(isSoPExpression("(X'*Y) * (Z+W')") == false);
}

TEST_CASE("Invalid SoP: (A'*B*) + (C*D)") {
    REQUIRE(isSoPExpression("(A'*B*) + (C*D)") == false);
}

TEST_CASE("Valid SoP: A*B*C'") {
    REQUIRE(isSoPExpression("A*B*C'") == true);
}

TEST_CASE("Valid SoP: (J'*K*L M*N)") {
    REQUIRE(isSoPExpression("(J'*K*L M*N)") == true);
}

TEST_CASE("Valid SoP: (U*V') + W*X + (Y*Z)") {
    REQUIRE(isSoPExpression("(U*V') + W*X + (Y*Z)") == true);
}

TEST_CASE("Inalid SoP: (G*H*I') + (A*B'") {
    REQUIRE(isSoPExpression("(G*H*I') + (A*B'") == false);
}
TEST_CASE("Invalid SoP: 55555") {
    REQUIRE(isSoPExpression("55555") == false);
}
TEST_CASE("Valid SoP: Hamada") {
    REQUIRE(isSoPExpression("Hamada") == true);
}
TEST_CASE("Validation of SoP expression: a + b'c + d'e") {
    REQUIRE(isSoPExpression("a + b'c + d'e") == true);
}

TEST_CASE("Validation of SoP expression: a'bc' + def + g'h'i'") {
    REQUIRE(isSoPExpression("a'bc' + def + g'h'i'") == true);
}

TEST_CASE("Validation of SoP expression: w'x'y + z") {
    REQUIRE(isSoPExpression("w'x'y + z") == true);
}

TEST_CASE("Validation of SoP expression: m'n + op'q'r'") {
    REQUIRE(isSoPExpression("m'n + op'q'r'") == true);
}

TEST_CASE("Validation of SoP expression: uv + w'x'y'z") {
    REQUIRE(isSoPExpression("uv + w'x'y'z") == true);
}
TEST_CASE("Validation of SoP expression: a' + b' + c") {
    REQUIRE(isSoPExpression("a' + b' + c") == true);
}

TEST_CASE("Validation of SoP expression: a*b + cd' + e'f'g") {
    REQUIRE(isSoPExpression("a*b + cd' + e'f'g") == true);
}

TEST_CASE("Validation of SoP expression: a(b*c)") {
    REQUIRE(isSoPExpression("a(b*c)") == true);
}

TEST_CASE("Validation of SoP expression: ab'c + d+e + f'gh'") {
    REQUIRE(isSoPExpression("ab'c + d+e + f'gh'") == true);
}

TEST_CASE("Validation of SoP expression: (a*b)(c*d)") {
    REQUIRE(isSoPExpression("(a*b)(c*d)") == true);
}

TEST_CASE("Validation of SoP expression: a*b*c'*d'e'f") {
    REQUIRE(isSoPExpression("a*b*c'*d'e'f") == true);
}

TEST_CASE("Validation of SoP expression: abc*def*g'hi") {
    REQUIRE(isSoPExpression("abc*def*g'hi") == true);
}
// Test cases for valid SoP expressions
TEST_CASE("Validation of SoP: (a * b) + (c * d')") {
    REQUIRE(isSoPExpression("(a * b) + (c * d')") == true);
}

TEST_CASE("Validation of SoP: a + b") {
    REQUIRE(isSoPExpression("a + b") == true);
}

TEST_CASE("Validation of SoP: (a * b * c) + d") {
    REQUIRE(isSoPExpression("(a * b * c) + d") == true);
}

TEST_CASE("Validation of SoP: x + (y * z')") {
    REQUIRE(isSoPExpression("x + (y * z')") == true);
}

TEST_CASE("Validation of SoP: (m * n') + o") {
    REQUIRE(isSoPExpression("(m * n') + o") == true);
}

// Test cases for invalid SoP expressions
TEST_CASE("Validation of SoP: a * b") {
    REQUIRE(isSoPExpression("a * b") == true);
}

TEST_CASE("Validation of non-SoP: (a + b) * c") {
    REQUIRE(isSoPExpression("(a + b) * c") == false);
}

TEST_CASE("Validation of SoP: (x * y) * z") {
    REQUIRE(isSoPExpression("(x * y) * z") == true);
}

TEST_CASE("Validation of non-SoP: (a + b') * (c + d)") {
    REQUIRE(isSoPExpression("(a + b') * (c + d)") == false);
}

TEST_CASE("Validation of SoP: w + x + y * z") {
    REQUIRE(isSoPExpression("w + x + y * z") == true);
}
TEST_CASE("Validation of non_SoP expression: a*") {
    REQUIRE(isSoPExpression("a*") == false);
}

TEST_CASE("Validation of non_SoP expression: a + b* + c") {
    REQUIRE(isSoPExpression("a + b* + c") == false);
}

TEST_CASE("Validation of non_SoP expression: a + b + c*") {
    REQUIRE(isSoPExpression("a + b + c*") == false);
}

TEST_CASE("Validation of non_SoP expression: **a + b") {
    REQUIRE(isSoPExpression("**a + b") == false);
}

TEST_CASE("Validation of non_SoP expression: a + ") {
    REQUIRE(isSoPExpression("a + ") == false);
}

TEST_CASE("Validation of non_SoP expression: a + + b") {
    REQUIRE(isSoPExpression("a + + b") == false);
}

TEST_CASE("Validation of SoP expression: a * b * c") {
    REQUIRE(isSoPExpression("a * b * c") == true);
}

TEST_CASE("Validation of expression: 'a + b") {
    REQUIRE(isSoPExpression("'a + b") == false);
}

TEST_CASE("Validation of expression: a + b*c + d") {
    REQUIRE(isSoPExpression("a + b*c + d") == true);
}

TEST_CASE("Validation of non_SoP expression: a**b + c") {
    REQUIRE(isSoPExpression("a**b + c") == false);
}

TEST_CASE("Validation of SoP expression: a' * b") {
    REQUIRE(isSoPExpression("a' * b") == true);
}

TEST_CASE("Validation of SoP expression: a * b' + c'") {
    REQUIRE(isSoPExpression("a * b' + c'") == true);
}

TEST_CASE("Validation of expression: a + (b * c)") {
    REQUIRE(isSoPExpression("a + (b * c)") == true);
}

TEST_CASE("Validation of expression: a*b' * c*d") {
    REQUIRE(isSoPExpression("a*b' * c*d") == true);
}

TEST_CASE("Validation of non_SoP expression: a*b* + c*d") {
    REQUIRE(isSoPExpression("a*b* + c*d") == false);
}

TEST_CASE("Validation of non_SoP expression: a++b * c") {
    REQUIRE(isSoPExpression("a++b * c") == false);
}

TEST_CASE("Validation of non_SoP expression: a*'*b") {
    REQUIRE(isSoPExpression("a*'*b") == false);
}

TEST_CASE("Validation of non_SoP expression: '") {
    REQUIRE(isSoPExpression("'") == false);
}

TEST_CASE("Validation of SoP expression: a*b'c*d") {
    REQUIRE(isSoPExpression("a*b'c*d") == true);
}

TEST_CASE("Validation of non_SoP expression: a*b + + c*d") {
    REQUIRE(isSoPExpression("a*b + + c*d") == false);
}

