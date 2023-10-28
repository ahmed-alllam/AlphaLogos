#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>

#include "../src/qm/uncovered_minterms.h"

void compareMinterms(const vector<Minterm>& output,
                     const vector<Minterm>& expected) {
  sort(output.begin(), output.end());
  sort(expected.begin(), expected.end());
  REQUIRE(output.size() == expected.size());

  for (const auto& expected_minterm : expected) {
    bool found = false;
    for (const auto& output_minterm : output) {
      if (expected_minterm.index == output_minterm.index) {
        found = true;
        INFO("Expected minterm: " << expected_minterm.index);
        INFO("Output minterm: " << output_minterm.index);
        REQUIRE(expected_minterm == output_minterm);
        break;
      }
    }
    INFO("Expected minterm not found: " << expected_minterm.index);
    REQUIRE(found);
  }
}

TEST_CASE("All minterms covered by essential implicants") {
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

TEST_CASE("Some minterms covered by essential implicants") {
  vector<Minterm> minterms = {{0, {0, 0}, 0, false},
                              {1, {0, 1}, 1, false},
                              {2, {1, 0}, 1, false},
                              {3, {1, 1}, 2, false}};
  vector<Implicant> essentialImplicants = {{{1}, {0, 1}, true, true, false},
                                           {{3, 2}, {1, 0}, true, true, false}};
  vector<Minterm> uncoveredMinterms =
      getUncoveredMinterms(minterms, essentialImplicants);
  REQUIRE(uncoveredMinterms == vector<Minterm>{{0, {0, 0}, 0, false}});
  compareMinterms(uncoveredMinterms, vector<Minterm>{{0, {0, 0}, 0, false}});
}