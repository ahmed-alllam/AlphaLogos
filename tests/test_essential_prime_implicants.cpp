#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>

#include "../src/qm/essential_prime_implicants.h"

TEST_CASE("Essential Prime Implicants") {
  vector<Implicant> primeImplicants = 
    {{{0, 2, 4, 6}, {0, -1, -1, 0}, false, false, false},
    {{0, 1, 8, 9}, {-1, 0, 0, -1}, false, false, false},
    {{9, 11, 13, 15}, {1, -1, -1, 1}, false, false, false}};

  vector<Implicant> expectedEssentialImplicants = 
    {{{0, 1, 8, 9}, {-1, 0, 0, -1}, false, false, false},
    {{0, 2, 4, 6}, {0, -1, -1, 0}, false, false, false},
    {{9, 11, 13, 15}, {1, -1, -1, 1}, false, false, false}};

  REQUIRE(generateEssentialPrimeImplicants(primeImplicants) ==
          expectedEssentialImplicants);
}


TEST_CASE("Essential Prime Implicants when no PIs are essential") {
  vector<Implicant> primeImplicants = {
      {{0, 1, 2, 3}, {-1, -1}, false, false, false},
      {{0, 1}, {0, -1}, false, false, false},
      {{2, 3}, {1, -1}, false, false, false}};

  vector<Implicant> expectedEssentialImplicants = {};

  REQUIRE(generateEssentialPrimeImplicants(primeImplicants) ==
          expectedEssentialImplicants);
}

TEST_CASE("Essential Prime Implicants for mixed scenario") {
  vector<Implicant> primeImplicants = {
      {{0, 1, 4, 5}, {-1, 0, -1}, false, false, false},
      {{0, 1}, {0, 0, -1}, false, false, false},
      {{2, 3, 6, 7}, {1, -1, -1}, false, false, false},
      {{6, 7}, {1, 1, -1}, false, false, false}};

  vector<Implicant> expectedEssentialImplicants = {
      {{0, 1, 4, 5}, {-1, 0, -1}, false, false, false},
      {{2, 3, 6, 7}, {1, -1, -1}, false, false, false}};

  REQUIRE(generateEssentialPrimeImplicants(primeImplicants) ==
          expectedEssentialImplicants);
}

TEST_CASE("Essential Prime Implicants ") {
  vector<Implicant> primeImplicants =
    {{{10, 26}, {0, -1, 1, 0, 1, 0}, false, false, false},
    {{10, 42}, {-1, 0, 1, 0, 1, 0}, false, false, false},
    {{18, 26}, {0, 1, -1, 0, 1, 0}, false, false, false},
    {{18, 50}, {-1, 1, 0, 0, 1, 0}, false, false, false},
    {{40, 42}, {1, 0, 1, 0, -1, 0}, false, false, false},
    {{48, 50}, {1, 1, 0, 0, -1, 0}, false, false, false},
    {{40, 41, 56, 57}, {1, -1, 1, 0, 0, -1}, false, false, false},
    {{48, 49, 52, 53, 56, 57, 60, 61}, {1, 1, -1, -1, 0, -1}, false, false, false}};

  vector<Implicant> expectedEssentialImplicants = 
    {
    {{40, 41, 56, 57}, {1, -1, 1, 0, 0, -1}, false, false, false},
    {{48, 49, 52, 53, 56, 57, 60, 61}, {1, 1, -1, -1, 0, -1}, false, false, false}};

  REQUIRE(generateEssentialPrimeImplicants(primeImplicants) ==
          expectedEssentialImplicants);
}
