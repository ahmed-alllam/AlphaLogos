#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include <string>
#include <vector>

#include "../src/logic_utils/canonical_forms.h"
#include "../src/logic_utils/maxterm.h"
#include "../src/logic_utils/minterm.h"
#include "../src/logic_utils/token.h"
#include "../src/logic_utils/truth_table_generator.h"

TEST_CASE("Validation of canonical SoP and PoS of  A + B * C' ") {
  string expr = "A + B * C'";
  vector<Token> expressionTokens = tokenize(expr);
  vector<Token> uniqueVariables = getUniqueVariables(expressionTokens);

  vector<vector<bool>> truthTable = generateTruthTable(expressionTokens);

  vector<Minterm> minterms = generateMinTerms(uniqueVariables, truthTable);

  vector<Maxterm> maxterms = generateMaxTerms(uniqueVariables, truthTable);

  string mintermsString = canonicalSoPToString(minterms, uniqueVariables);
  string maxtermsString = canonicalPoSToString(maxterms, uniqueVariables);

  REQUIRE(mintermsString == "AB'C'+A'BC'+ABC'+AB'C+ABC");
  REQUIRE(maxtermsString == "(A+B+C)(A+B+C')(A+B'+C')");
}

TEST_CASE("Validation of canonical SoP and PoS of  a'bc + ab' + bc' ") {
  string expr = "a'bc + ab' + bc'";
  vector<Token> expressionTokens = tokenize(expr);
  vector<Token> uniqueVariables = getUniqueVariables(expressionTokens);

  vector<vector<bool>> truthTable = generateTruthTable(expressionTokens);

  vector<Minterm> minterms = generateMinTerms(uniqueVariables, truthTable);

  vector<Maxterm> maxterms = generateMaxTerms(uniqueVariables, truthTable);

  string mintermsString = canonicalSoPToString(minterms, uniqueVariables);
  string maxtermsString = canonicalPoSToString(maxterms, uniqueVariables);

  REQUIRE(mintermsString == "ab'c'+a'bc'+abc'+ab'c+a'bc");
  REQUIRE(maxtermsString == "(a+b+c)(a+b+c')(a'+b'+c')");
}

TEST_CASE("Validation of canonical SoP and PoS of  a+b+c+d ") {
  string expr = "a+b+c+d";
  vector<Token> expressionTokens = tokenize(expr);
  vector<Token> uniqueVariables = getUniqueVariables(expressionTokens);

  vector<vector<bool>> truthTable = generateTruthTable(expressionTokens);

  vector<Minterm> minterms = generateMinTerms(uniqueVariables, truthTable);

  vector<Maxterm> maxterms = generateMaxTerms(uniqueVariables, truthTable);

  string mintermsString = canonicalSoPToString(minterms, uniqueVariables);
  string maxtermsString = canonicalPoSToString(maxterms, uniqueVariables);

  REQUIRE(mintermsString ==
          "ab'c'd'+a'bc'd'+abc'd'+a'b'cd'+ab'cd'+a'bcd'+abcd'+a'b'c'd+ab'c'd+a'"
          "bc'd+abc'd+a'b'cd+ab'cd+a'bcd+abcd");
  REQUIRE(maxtermsString == "(a+b+c+d)");
}