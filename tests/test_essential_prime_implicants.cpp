#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>

#include "../src/qm/essential_prime_implicants.h"

TEST_CASE("Essential Prime Implicants when all PIs are essential") {
  vector<Implicant> primeImplicants = {{{0, 1}, {0, -1}, false, false, false},
                                       {{2, 3}, {1, -1}, false, false, false}};

  vector<Implicant> expectedEssentialImplicants = primeImplicants;

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
