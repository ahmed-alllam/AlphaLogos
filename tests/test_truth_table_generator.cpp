#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include <unordered_map>

#include "../src/logic_utils/truth_table_generator.h"

using namespace std;

bool validateTruthTable(
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

TEST_CASE("Truth table for expression A + B * C' ") {
  string expr = "A + B * C' ";

  std::unordered_map<std::vector<bool>, bool> expected = {
      {{true, true, true}, true},   {{true, true, false}, true},
      {{true, false, true}, true},  {{false, false, true}, false},
      {{true, false, false}, true}, {{false, true, true}, false},
      {{false, true, false}, true}, {{false, false, false}, false}};

  REQUIRE(validateTruthTable(expected, expr) == true);
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

  REQUIRE(validateTruthTable(expected, expr) == true);
}

TEST_CASE("Truth table for expression (a+bc)(a+(b+c+d)(cd))") {
  string expr = "(a+bc)(a+(b+c+d)(cd))";

  std::unordered_map<std::vector<bool>, bool> expected = {
      {{true, true, true, true}, true},
      {{true, true, true, false}, true},
      {{true, true, false, true}, true},
      {{true, true, false, false}, true},
      {{true, false, true, true}, true},
      {{true, false, true, false}, true},
      {{true, false, false, true}, true},
      {{true, false, false, false}, true},
      {{false, true, true, true}, true},
      {{false, true, true, false}, false},
      {{false, true, false, true}, false},
      {{false, true, false, false}, false},
      {{false, false, true, true}, false},
      {{false, false, true, false}, false},
      {{false, false, false, true}, false},
      {{false, false, false, false}, false}};

  REQUIRE(validateTruthTable(expected, expr) == true);
}

TEST_CASE(
    "Truth table for complex nested expression (((a' + b(c' + d)))(c + a(b' + "
    "d)))") {
  string expr = "(((a' + b(c' + d)))(c + a(b' + d)))";

  std::unordered_map<std::vector<bool>, bool> expected = {
      {{true, true, true, true}, true},
      {{true, true, true, false}, false},
      {{true, true, false, true}, true},
      {{true, true, false, false}, false},
      {{true, false, true, true}, false},
      {{true, false, true, false}, false},
      {{true, false, false, true}, false},
      {{true, false, false, false}, false},
      {{false, true, true, true}, true},
      {{false, true, true, false}, true},
      {{false, true, false, true}, false},
      {{false, true, false, false}, false},
      {{false, false, true, true}, true},
      {{false, false, true, false}, true},
      {{false, false, false, true}, false},
      {{false, false, false, false}, false}};

  REQUIRE(validateTruthTable(expected, expr) == true);
}

TEST_CASE(
    "Truth table for expression A B C' D E G' + A' B C D' E' G + A B' C D G' + "
    "A' B' C' D G + E G A' B' C") {
  string expr =
      "( A B C ' D E G ' ) + ( A ' B C D ' E ' G ) +  A B ' C D G ' + ( A ' B "
      "' C ' D G ) + ( E G A ' B ' C )";

  std::unordered_map<std::vector<bool>, bool> expected = {

      {{true, true, true, true, true, true}, false},
      {{true, true, true, true, true, false}, false},
      {{true, true, true, true, false, true}, false},
      {{true, true, true, true, false, false}, false},
      {{true, true, true, false, true, true}, false},
      {{true, true, true, false, true, false}, false},
      {{true, true, true, false, false, true}, false},
      {{true, true, true, false, false, false}, false},
      {{true, true, false, true, true, true}, false},
      {{true, true, false, true, true, false}, true},
      {{true, true, false, true, false, true}, false},
      {{true, true, false, true, false, false}, false},
      {{true, true, false, false, true, true}, false},
      {{true, true, false, false, true, false}, false},
      {{true, true, false, false, false, true}, false},
      {{true, true, false, false, false, false}, false},
      {{true, false, true, true, true, true}, false},
      {{true, false, true, true, true, false}, true},
      {{true, false, true, true, false, true}, false},
      {{true, false, true, true, false, false}, true},
      {{true, false, true, false, true, true}, false},
      {{true, false, true, false, true, false}, false},
      {{true, false, true, false, false, true}, false},
      {{true, false, true, false, false, false}, false},
      {{true, false, false, true, true, true}, false},
      {{true, false, false, true, true, false}, false},
      {{true, false, false, true, false, true}, false},
      {{true, false, false, true, false, false}, false},
      {{true, false, false, false, true, true}, false},
      {{true, false, false, false, true, false}, false},
      {{true, false, false, false, false, true}, false},
      {{true, false, false, false, false, false}, false},
      {{false, true, true, true, true, true}, false},
      {{false, true, true, true, true, false}, false},
      {{false, true, true, true, false, true}, false},
      {{false, true, true, true, false, false}, false},
      {{false, true, true, false, true, true}, false},

      {{false, true, true, false, true, false}, false},
      {{false, true, true, false, false, true}, true},
      {{false, true, true, false, false, false}, false},
      {{false, true, false, true, true, true}, false},
      {{false, true, false, true, true, false}, false},
      {{false, true, false, true, false, true}, false},
      {{false, true, false, true, false, false}, false},
      {{false, true, false, false, true, true}, false},
      {{false, true, false, false, true, false}, false},
      {{false, true, false, false, false, true}, false},
      {{false, true, false, false, false, false}, false},
      {{false, false, true, true, true, true}, true},
      {{false, false, true, true, true, false}, false},
      {{false, false, true, true, false, true}, false},
      {{false, false, true, true, false, false}, false},
      {{false, false, true, false, true, true}, true},
      {{false, false, true, false, true, false}, false},
      {{false, false, true, false, false, true}, false},
      {{false, false, true, false, false, false}, false},
      {{false, false, false, true, true, true}, true},
      {{false, false, false, true, true, false}, false},
      {{false, false, false, true, false, true}, true},
      {{false, false, false, true, false, false}, false},
      {{false, false, false, false, true, true}, false},
      {{false, false, false, false, true, false}, false},
      {{false, false, false, false, false, true}, false},
      {{false, false, false, false, false, false}, false}

  };

  REQUIRE(validateTruthTable(expected, expr) == true);
}

TEST_CASE("Truth table for expression a'bc + ab' + bc'") {
  string expr = "a'bc + ab' + bc'";

  std::unordered_map<std::vector<bool>, bool> expected = {
      {{true, true, true}, false},   {{true, true, false}, true},
      {{true, false, true}, true},   {{true, false, false}, true},
      {{false, true, true}, true},   {{false, true, false}, true},
      {{false, false, true}, false}, {{false, false, false}, false}};

  REQUIRE(validateTruthTable(expected, expr) == true);
}

TEST_CASE("Truth table for expression cd+b'c+ a d") {
  string expr = "cd+b'c+ a d";

  std::unordered_map<std::vector<bool>, bool> expected = {
      {{true, true, true, true}, true},
      {{true, true, true, false}, true},
      {{true, true, false, true}, true},
      {{true, true, false, false}, true},
      {{true, false, true, true}, false},
      {{true, false, true, false}, false},
      {{true, false, false, true}, true},
      {{true, false, false, false}, true},
      {{false, true, true, true}, true},
      {{false, true, true, false}, false},
      {{false, true, false, true}, true},
      {{false, true, false, false}, false},
      {{false, false, true, true}, false},
      {{false, false, true, false}, false},
      {{false, false, false, true}, false},
      {{false, false, false, false}, false}};

  REQUIRE(validateTruthTable(expected, expr) == true);
}

TEST_CASE("Truth table for expression aa'") {
  string expr = "aa'";

  std::unordered_map<std::vector<bool>, bool> expected = {{{true}, false},
                                                          {{false}, false}};

  REQUIRE(validateTruthTable(expected, expr) == true);
}

TEST_CASE("Truth table for expression a + a'") {
  string expr = "a + a'";

  std::unordered_map<std::vector<bool>, bool> expected = {{{true}, true},
                                                          {{false}, true}};

  REQUIRE(validateTruthTable(expected, expr) == true);
}

TEST_CASE("Truth table for expression (a) + (a)'") {
  string expr = "(a) + (a)'";

  std::unordered_map<std::vector<bool>, bool> expected = {{{true}, true},
                                                          {{false}, true}};

  REQUIRE(validateTruthTable(expected, expr) == true);
}

TEST_CASE("Truth table for expression (((a))) + (a)'") {
  string expr = "(((a))) + (a)'";

  std::unordered_map<std::vector<bool>, bool> expected = {{{true}, true},
                                                          {{false}, true}};

  REQUIRE(validateTruthTable(expected, expr) == true);
}

TEST_CASE("Truth table for expression (a') + (b')") {
  string expr = "(a') + (b')";

  std::unordered_map<std::vector<bool>, bool> expected = {
      {{false, false}, true},
      {{false, true}, true},
      {{true, false}, true},
      {{true, true}, false}};

  REQUIRE(validateTruthTable(expected, expr) == true);
}

TEST_CASE("Truth table for expression       (    a ) * (b       )") {
  string expr = "      (    a ) * (b       )";

  std::unordered_map<std::vector<bool>, bool> expected = {
      {{false, false}, false},
      {{false, true}, false},
      {{true, false}, false},
      {{true, true}, true}};
  REQUIRE(validateTruthTable(expected, expr) == true);
}

TEST_CASE("Truth table for expression  (((a')')'*(b)')") {
  string expr = "(((a')')'*(b)')";

  std::unordered_map<std::vector<bool>, bool> expected = {
      {{false, false}, true},
      {{false, true}, false},
      {{true, false}, false},
      {{true, true}, false}};
  REQUIRE(validateTruthTable(expected, expr) == true);
}

TEST_CASE("Truth table for expression  (((a')')'(b)')'") {
  string expr = "(((a')')'(b)')'";

  std::unordered_map<std::vector<bool>, bool> expected = {
      {{false, false}, false},
      {{false, true}, true},
      {{true, false}, true},
      {{true, true}, true}};
  REQUIRE(validateTruthTable(expected, expr) == true);
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

TEST_CASE("Truth table for expression a'' + b") {
  string expr = "a'' + b";

  std::unordered_map<std::vector<bool>, bool> expected = {
      {{false, false}, false},
      {{false, true}, true},
      {{true, false}, true},
      {{true, true}, true}};
  REQUIRE(validateTruthTable(expected, expr) == true);
}

TEST_CASE("Truth table for expression  (a+b)'' + b''' + ab''  ") {
  string expr = "(a+b)'' + b''' + ab' ";

  std::unordered_map<std::vector<bool>, bool> expected = {
      {{false, false}, true},
      {{false, true}, true},
      {{true, false}, true},
      {{true, true}, true}};

  REQUIRE(validateTruthTable(expected, expr) == true);
}
