#define CATCH_CONFIG_MAIN

#include <algorithm>
#include <catch2/catch_test_macros.hpp>

#include "../src/qm/uncovered_minterms.h"

void compareMinterms(vector<Minterm>& output, vector<Minterm>& expected) {
  REQUIRE(output.size() == expected.size());

  for (auto& expected_minterm : expected) {
    bool found = false;
    for (auto& output_minterm : output) {
      if (expected_minterm.index == output_minterm.index) {
        found = true;
        INFO("Expected minterm: " << expected_minterm.index);
        INFO("Output minterm: " << output_minterm.index);
        REQUIRE(expected_minterm.index == output_minterm.index);
        break;
      }
    }
    INFO("Expected minterm not found: " << expected_minterm.index);
    REQUIRE(found);
  }
}

TEST_CASE("Test Minterms not covered by essential implicants (1)") {
  vector<Minterm> minterms = {{0, {0, 0}, 0, false},
                              {1, {0, 1}, 1, false},
                              {2, {1, 0}, 1, false},
                              {3, {1, 1}, 2, false}};
  vector<Implicant> essentialImplicants = {
      {{1, 0}, {-1, 1}, true, true, false},
      {{3, 2}, {1, -1}, true, true, false}};
  vector<Minterm> uncoveredMinterms =
      getUncoveredMinterms(minterms, essentialImplicants);
  REQUIRE(uncoveredMinterms.empty());
}

TEST_CASE("Test Minterms not covered by essential implicants (2)") {
  vector<Minterm> minterms = {{0, {0, 0}, 0, false},
                              {1, {0, 1}, 1, false},
                              {2, {1, 0}, 1, false},
                              {3, {1, 1}, 2, false}};
  vector<Implicant> essentialImplicants = {{{1}, {0, 1}, true, true, false},
                                           {{3, 2}, {1, 0}, true, true, false}};
  vector<Minterm> uncoveredMinterms =
      getUncoveredMinterms(minterms, essentialImplicants);
    
  vector<Minterm> expected = {{0, {0, 0}, 0, false}};

  compareMinterms(uncoveredMinterms, expected);
}

TEST_CASE("Test Minterms not covered by essential implicants (3)") {
  vector<Minterm> minterms = {{0, {0, 0}, 0, false},
                              {1, {0, 1}, 1, false},
                              {2, {1, 0}, 1, false},
                              {3, {1, 1}, 2, false}};
  vector<Implicant> essentialImplicants = {{{1}, {0, 1}, true, true, false},
                                           {{3, 2}, {1, 0}, true, true, false}};
  vector<Minterm> uncoveredMinterms =
      getUncoveredMinterms(minterms, essentialImplicants);
    
  vector<Minterm> expected = {{0, {0, 0}, 0, false}};

  compareMinterms(uncoveredMinterms, expected);
}
