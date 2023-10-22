#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>

#include "../src/logic_utils/SoP_validator.h"

TEST_CASE("Validation of expression x + y") {
  REQUIRE(isValidSoP("x + y") == true);
}

TEST_CASE("Valid SoP: (A*B') + (C*D)") {
  REQUIRE(isValidSoP("(A*B') + (C*D)") == true);
}

TEST_CASE("Valid SoP: (X'*Y) + (Z*W') + (M*N)") {
  REQUIRE(isValidSoP("(X'*Y) + (Z*W') + (M*N)") == true);
}

TEST_CASE("Valid SoP: (A*B*C')") { REQUIRE(isValidSoP("(A*B*C')") == true); }

TEST_CASE("Valid SoP: (J'*K*L) + (N*O'*P)") {
  REQUIRE(isValidSoP("(J'*K*L) + (N*O'*P)") == true);
}

TEST_CASE("Valid SoP: (U*V') + (W*X) + (Y*Z)") {
  REQUIRE(isValidSoP("(U*V') + (W*X) + (Y*Z)") == true);
}

TEST_CASE("Valid SoP: (G*H*I')") { REQUIRE(isValidSoP("(G*H*I')") == true); }

TEST_CASE("Valid SoP: (A+B) + (C*D)") {
  REQUIRE(isValidSoP("(A+B) + (C*D)") == true);
}

TEST_CASE("Invalid SoP: (X'*Y) * (Z+W')") {
  REQUIRE(isValidSoP("(X'*Y) * (Z+W')") == false);
}

TEST_CASE("Invalid SoP: (A'*B*) + (C*D)") {
  REQUIRE(isValidSoP("(A'*B*) + (C*D)") == false);
}

TEST_CASE("Valid SoP: A*B*C'") { REQUIRE(isValidSoP("A*B*C'") == true); }

TEST_CASE("Valid SoP: (J'*K*L M*N)") {
  REQUIRE(isValidSoP("(J'*K*L M*N)") == true);
}

TEST_CASE("Valid SoP: (U*V') + W*X + (Y*Z)") {
  REQUIRE(isValidSoP("(U*V') + W*X + (Y*Z)") == true);
}

TEST_CASE("Inalid SoP: (G*H*I') + (A*B'") {
  REQUIRE(isValidSoP("(G*H*I') + (A*B'") == false);
}
TEST_CASE("Invalid SoP: 55555") { REQUIRE(isValidSoP("55555") == false); }
TEST_CASE("Valid SoP: Hamada") { REQUIRE(isValidSoP("Hamada") == true); }
TEST_CASE("Validation of SoP expression: a + b'c + d'e") {
  REQUIRE(isValidSoP("a + b'c + d'e") == true);
}

TEST_CASE("Validation of SoP expression: a'bc' + def + g'h'i'") {
  REQUIRE(isValidSoP("a'bc' + def + g'h'i'") == true);
}

TEST_CASE("Validation of SoP expression: w'x'y + z") {
  REQUIRE(isValidSoP("w'x'y + z") == true);
}

TEST_CASE("Validation of SoP expression: m'n + op'q'r'") {
  REQUIRE(isValidSoP("m'n + op'q'r'") == true);
}

TEST_CASE("Validation of SoP expression: uv + w'x'y'z") {
  REQUIRE(isValidSoP("uv + w'x'y'z") == true);
}
TEST_CASE("Validation of SoP expression: a' + b' + c") {
  REQUIRE(isValidSoP("a' + b' + c") == true);
}

TEST_CASE("Validation of SoP expression: a*b + cd' + e'f'g") {
  REQUIRE(isValidSoP("a*b + cd' + e'f'g") == true);
}

TEST_CASE("Validation of SoP expression: a(b*c)") {
  REQUIRE(isValidSoP("a(b*c)") == true);
}

TEST_CASE("Validation of SoP expression: ab'c + d+e + f'gh'") {
  REQUIRE(isValidSoP("ab'c + d+e + f'gh'") == true);
}

TEST_CASE("Validation of SoP expression: (a*b)(c*d)") {
  REQUIRE(isValidSoP("(a*b)(c*d)") == true);
}

TEST_CASE("Validation of SoP expression: a*b*c'*d'e'f") {
  REQUIRE(isValidSoP("a*b*c'*d'e'f") == true);
}

TEST_CASE("Validation of SoP expression: abc*def*g'hi") {
  REQUIRE(isValidSoP("abc*def*g'hi") == true);
}
// Test cases for valid SoP expressions
TEST_CASE("Validation of SoP: (a * b) + (c * d')") {
  REQUIRE(isValidSoP("(a * b) + (c * d')") == true);
}

TEST_CASE("Validation of SoP: a + b") { REQUIRE(isValidSoP("a + b") == true); }

TEST_CASE("Validation of SoP: (a * b * c) + d") {
  REQUIRE(isValidSoP("(a * b * c) + d") == true);
}

TEST_CASE("Validation of SoP: x + (y * z')") {
  REQUIRE(isValidSoP("x + (y * z')") == true);
}

TEST_CASE("Validation of SoP: (m * n') + o") {
  REQUIRE(isValidSoP("(m * n') + o") == true);
}

// Test cases for invalid SoP expressions
TEST_CASE("Validation of SoP: a * b") { REQUIRE(isValidSoP("a * b") == true); }

TEST_CASE("Validation of non-SoP: (a + b) * c") {
  REQUIRE(isValidSoP("(a + b) * c") == false);
}

TEST_CASE("Validation of SoP: (x * y) * z") {
  REQUIRE(isValidSoP("(x * y) * z") == true);
}

TEST_CASE("Validation of non-SoP: (a + b') * (c + d)") {
  REQUIRE(isValidSoP("(a + b') * (c + d)") == false);
}

TEST_CASE("Validation of SoP: w + x + y * z") {
  REQUIRE(isValidSoP("w + x + y * z") == true);
}
TEST_CASE("Validation of non_SoP expression: a*") {
  REQUIRE(isValidSoP("a*") == false);
}

TEST_CASE("Validation of non_SoP expression: a + b* + c") {
  REQUIRE(isValidSoP("a + b* + c") == false);
}

TEST_CASE("Validation of non_SoP expression: a + b + c*") {
  REQUIRE(isValidSoP("a + b + c*") == false);
}

TEST_CASE("Validation of non_SoP expression: **a + b") {
  REQUIRE(isValidSoP("**a + b") == false);
}

TEST_CASE("Validation of non_SoP expression: a + ") {
  REQUIRE(isValidSoP("a + ") == false);
}

TEST_CASE("Validation of non_SoP expression: a + + b") {
  REQUIRE(isValidSoP("a + + b") == false);
}

TEST_CASE("Validation of SoP expression: a * b * c") {
  REQUIRE(isValidSoP("a * b * c") == true);
}

TEST_CASE("Validation of expression: 'a + b") {
  REQUIRE(isValidSoP("'a + b") == false);
}

TEST_CASE("Validation of expression: a + b*c + d") {
  REQUIRE(isValidSoP("a + b*c + d") == true);
}

TEST_CASE("Validation of non_SoP expression: a**b + c") {
  REQUIRE(isValidSoP("a**b + c") == false);
}

TEST_CASE("Validation of SoP expression: a' * b") {
  REQUIRE(isValidSoP("a' * b") == true);
}

TEST_CASE("Validation of SoP expression: a * b' + c'") {
  REQUIRE(isValidSoP("a * b' + c'") == true);
}

TEST_CASE("Validation of expression: a + (b * c)") {
  REQUIRE(isValidSoP("a + (b * c)") == true);
}

TEST_CASE("Validation of expression: a*b' * c*d") {
  REQUIRE(isValidSoP("a*b' * c*d") == true);
}

TEST_CASE("Validation of non_SoP expression: a*b* + c*d") {
  REQUIRE(isValidSoP("a*b* + c*d") == false);
}

TEST_CASE("Validation of non_SoP expression: a++b * c") {
  REQUIRE(isValidSoP("a++b * c") == false);
}

TEST_CASE("Validation of non_SoP expression: a*'*b") {
  REQUIRE(isValidSoP("a*'*b") == false);
}

TEST_CASE("Validation of non_SoP expression: '") {
  REQUIRE(isValidSoP("'") == false);
}

TEST_CASE("Validation of SoP expression: a*b'c*d") {
  REQUIRE(isValidSoP("a*b'c*d") == true);
}

TEST_CASE("Validation of non_SoP expression: a*b + + c*d") {
  REQUIRE(isValidSoP("a*b + + c*d") == false);
}
