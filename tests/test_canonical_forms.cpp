#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include <unordered_map>

#include "../src/logic_utils/canonical_forms.h"

using namespace std;

bool validateCanonicalForms(
    const std::unordered_map<std::vector<bool>, bool> &expected,
    const string &expression) {
  vector<vector<bool>> generatedTruthTable = generateTruthTable(expression);

  for (const vector<bool> &row : generatedTruthTable) {
    vector<bool> input(row.begin(), row.end() - 1);
    bool output = row.back();

    if (expected.find(input) == expected.end() ||
        expected.at(input) != output) {
      return false;
    }
  }

  return true;
}

TEST_CASE("Truth table for expression  ((a')')'*(b)'") {
  string expr = "((a')')'*(b)'";

  std::unordered_map<std::vector<bool>, bool> expected = {
      {{false, false}, true},
      {{false, true}, false},
      {{true, false}, false},
      {{true, true}, false}};
  REQUIRE(validateTruthTable(expected, expr) == true);
}