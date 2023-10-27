#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>

#include "../src/qm/uncovered_minterms.h"

TEST_CASE("All minterms covered by essential implicants") {
  vector<Minterm> minterms = {{0, {0, 0}, 0, false},
                              {1, {0, 1}, 1, false},
                              {2, {1, 0}, 1, false},
                              {3, {1, 1}, 2, false}};
  vector<Implicant> essentialImplicants = {
      {{1, 0}, {-1, 1}, true, true, false},
      {{3, 2}, {1, -1}, true, true, false}};
  vector<int> uncoveredMinterms =
      getUncoveredMinterms(minterms, essentialImplicants);
  REQUIRE(uncoveredMinterms.empty());
}

TEST_CASE("Some minterms covered by essential implicants") {
  vector<Minterm> minterms = {{0, {0, 0}, 0, false},
                              {1, {0, 1}, 1, false},
                              {2, {1, 0}, 1, false},
                              {3, {1, 1}, 2, false}};
  vector<Implicant> essentialImplicants = {{{1}, {0, 1}, true, true, false},
                                           {{3, 2}, {1, 0}, true, true, false}};
  vector<int> uncoveredMinterms =
      getUncoveredMinterms(minterms, essentialImplicants);
  REQUIRE(uncoveredMinterms == vector<int>{0});
}