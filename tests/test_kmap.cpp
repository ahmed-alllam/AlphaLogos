#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include <vector>

#include "../src/qm/kmap.h"
#include "../src/qm/prime_implicants.h"

using namespace std;

string kmapToString(const vector<vector<string>> &kmap) {
  string result;
  for (const auto &row : kmap) {
    for (const auto &cell : row) {
      result += cell + " ";
    }
    result += "\n";
  }
  return result;
}

// All test cases done using the help of: https://atozmath.com/KMap.aspx?q=kmap

TEST_CASE("Test kmap for f(a, b, c)=Σm(0,2,3,6)") {
  vector<Token> variableTokens = {
      {TokenType::VAR, 'a'}, {TokenType::VAR, 'b'}, {TokenType::VAR, 'c'}};

  vector<Minterm> minterms = {{0, {0, 0, 0}, 0, false},
                              {2, {0, 1, 0}, 1, false},
                              {3, {0, 1, 1}, 2, false},
                              {6, {1, 1, 0}, 3, false}};

  vector<Implicant> primeImplicants = generatePrimeImplicants(minterms);

  vector<vector<string>> kmap =
      makeKMap(primeImplicants, variableTokens, minterms);

  string expected =
      "  b'c' b'c bc bc' \n"
      "a' 1 PI0 0 1 PI1 1 PI0 PI1 PI2 \n"
      "a 0 0 0 1 PI2 \n";

  REQUIRE(kmapToString(kmap) == expected);
}

TEST_CASE("Test kmap for f(a, b) = Σm(0, 1)") {
  vector<Token> variableTokens = {{TokenType::VAR, 'a'}, {TokenType::VAR, 'b'}};

  vector<Minterm> minterms = {{0, {0, 0}, 0, false}, {1, {0, 1}, 1, false}};

  vector<Implicant> primeImplicants = generatePrimeImplicants(minterms);

  vector<vector<string>> kmap =
      makeKMap(primeImplicants, variableTokens, minterms);

  string expected =
      "  b' b \n"
      "a' 1 PI0 1 PI0 \n"
      "a 0 0 \n";

  REQUIRE(kmapToString(kmap) == expected);
}

// test that it throws an error when there are more than 4 or less than 2
// variables
TEST_CASE("Test KMap for 1 variable") {
  vector<Token> variableTokens = {{TokenType::VAR, 'a'}};

  vector<Minterm> minterms = {{0, {0}, 0, false}, {1, {1}, 1, false}};

  vector<Implicant> primeImplicants = generatePrimeImplicants(minterms);

  REQUIRE_THROWS(makeKMap(primeImplicants, variableTokens, minterms));
}

TEST_CASE("Test KMap for 5 variables") {
  vector<Token> variableTokens = {{TokenType::VAR, 'a'},
                                  {TokenType::VAR, 'b'},
                                  {TokenType::VAR, 'c'},
                                  {TokenType::VAR, 'd'},
                                  {TokenType::VAR, 'e'}};

  vector<Minterm> minterms = {
      {2, {0, 0, 1, 0}, 1, false},  {6, {0, 1, 1, 0}, 2, false},
      {8, {1, 0, 0, 0}, 1, false},  {9, {1, 0, 0, 1}, 2, false},
      {10, {1, 0, 1, 0}, 2, false}, {11, {1, 0, 1, 1}, 3, false},
  };

  vector<Implicant> primeImplicants = generatePrimeImplicants(minterms);

  REQUIRE_THROWS(makeKMap(primeImplicants, variableTokens, minterms));
}

TEST_CASE("Test latex kmap for f(a, b, c)=Σm(0,2,3,6)") {
  vector<Token> variableTokens = {{TokenType::VAR, 'a'},
                                  {TokenType::VAR, 'b'},
                                  {TokenType::VAR, 'c'},
                                  {TokenType::VAR, 'd'}};

  vector<Minterm> minterms = {
      {0, {0, 0, 0, 0}, 0, false},
      {1, {0, 0, 0, 1}, 1, false},
      {2, {0, 0, 1, 0}, 1, false},
      {3, {0, 0, 1, 1}, 2, false},
      // {4, {0, 1, 0, 0}, 1, false},
      // {5, {0, 1, 0, 1}, 2, false},
      // {6, {0, 1, 1, 0}, 2, false},
      // {7, {0, 1, 1, 1}, 3, false},
      {8, {1, 0, 0, 0}, 1, false},
      {9, {1, 0, 0, 1}, 2, false},
      {10, {1, 0, 1, 0}, 2, false},
      {11, {1, 0, 1, 1}, 3, false}
      // {12, {1, 1, 0, 0}, 2, false},
      // {13, {1, 1, 0, 1}, 3, false},
      // {14, {1, 1, 1, 0}, 3, false},
      // {15, {1, 1, 1, 1}, 4, false}
  };

  vector<Implicant> primeImplicants = generatePrimeImplicants(minterms);

  string kmap = makeKMapLaTeX(primeImplicants, variableTokens, minterms);

  string expected =
      "  b'c' b'c bc bc' \n"
      "a' 1 PI0 0 1 PI1 1 PI0 PI1 PI2 \n"
      "a 0 0 0 1 PI2 \n";

  REQUIRE(kmap == expected);
}