#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include <unordered_map>

#include "../src/logic_utils/truth_table_generator.h"

using namespace std;

void compareTruthTables(std::unordered_map<std::vector<bool>, bool> expected,
                        vector<vector<bool>> result) {
  for (int i = 0; i < result.size(); i++) {
    vector<bool> permutation = result[i];

    vector<bool> permutationWithoutLast(permutation.begin(),
                                        permutation.end() - 1);

    bool last = permutation[permutation.size() - 1];

    REQUIRE(expected.find(permutationWithoutLast) != expected.end());

    INFO("The idx is " << i);

    REQUIRE(expected[permutationWithoutLast] == last);
  }
}

TEST_CASE("Truth table for expression A + B * !C") {
  string expr = "A + B * !C";

  std::unordered_map<std::vector<bool>, bool> expected = {
      {{true, true, true}, true},   {{true, true, false}, true},
      {{true, false, true}, true},  {{false, false, true}, false},
      {{true, false, false}, true}, {{false, true, true}, false},
      {{false, true, false}, true}, {{false, false, false}, false}};

  vector<vector<bool>> result = generateTruthTable(expr);

  compareTruthTables(expected, result);
}

TEST_CASE("Truth table for expression (A+D)*(B+C)") {
  string expr = "(A+D)*(B+C)";

  std::unordered_map<std::vector<bool>, bool> expected = {
      {{true, true, true, true}, true},
      {{true, true, true, false}, true},
      {{true, true, false, true}, true},
      {{true, true, false, false}, false},
      {{true, false, true, true}, true},
      {{true, false, true, false}, true},
      {{true, false, false, true}, true},
      {{true, false, false, false}, false},
      {{false, true, true, true}, true},
      {{false, true, true, false}, true},
      {{false, true, false, true}, true},
      {{false, true, false, false}, false},
      {{false, false, true, true}, false},
      {{false, false, true, false}, false},
      {{false, false, false, true}, false},
      {{false, false, false, false}, false}};

  vector<vector<bool>> result = generateTruthTable(expr);

  compareTruthTables(expected, result);
}
