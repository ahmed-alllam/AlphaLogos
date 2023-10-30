#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include <vector>

#include "../src/logic_utils/minterm.h"
#include "../src/logic_utils/token.h"
#include "../src/qm/implicant.h"
#include "../src/qm/petrick.h"
#include "../src/qm/prime_implicants.h"

using namespace std;

void comparebinary(const vector<Implicant>& output,
                   const vector<Implicant>& expected,
                   vector<Token> variableTokens) {
  REQUIRE(output.size() == output.size());

  // find the implicant in output that matches the implicant in expected
  for (const auto& expected_implicant : expected) {
    bool found = false;
    for (const auto& output_implicant : output) {
      if (expected_implicant.binary == output_implicant.binary) {
        found = true;
        INFO("Expected implicant: " << implicantToString(expected_implicant,
                                                         variableTokens));
        INFO("Output implicant: " << implicantToString(output_implicant,
                                                       variableTokens));
        REQUIRE(expected_implicant == output_implicant);
        break;
      }
    }
    INFO("Expected not found implicant: " << implicantToString(
             expected_implicant, variableTokens));
    REQUIRE(found);
  }
}

TEST_CASE(
    "Test petrick for f(a, b, c, "
    "d)=Σm(0,1,2,4,6,8,9,11,13,15") {
  vector<Token> variableTokens = {{TokenType::VAR, 'a'},
                                  {TokenType::VAR, 'b'},
                                  {TokenType::VAR, 'c'},
                                  {TokenType::VAR, 'd'}};

  vector<Implicant> implicants = {
      {{0, 2, 4, 6}, {0, -1, -1, 0}, false, false, false},
      {{0, 1, 8, 9}, {-1, 0, 0, -1}, false, false, false},
      {{9, 11, 13, 15}, {1, -1, -1, 1}, false, false, false},
  };

  vector<Implicant> output = petrick(implicants);

  vector<Implicant> expected = {
      {{0, 2, 4, 6}, {0, -1, -1, 0}, false, false, false},
      {{0, 1, 8, 9}, {-1, 0, 0, -1}, false, false, false},
      {{9, 11, 13, 15}, {1, -1, -1, 1}, false, false, false},
  };

  comparebinary(output, expected, variableTokens);
}

TEST_CASE("Test petrick for f(a, b, c, d)=Σm(2,6,8,9,10,11,14,15)") {
  vector<Token> variableTokens = {{TokenType::VAR, 'a'},
                                  {TokenType::VAR, 'b'},
                                  {TokenType::VAR, 'c'},
                                  {TokenType::VAR, 'd'}};

  vector<Implicant> implicant = {
      {{2, 6, 10, 14}, {-1, -1, 1, 0}, false, false, false},
      {{8, 9, 10, 11}, {1, 0, -1, -1}, false, false, false},
      {{10, 11, 14, 15}, {1, -1, 1, -1}, false, false, false},
  };

  vector<Implicant> output = petrick(implicant);

  vector<Implicant> expected = {
      {{2, 6, 10, 14}, {-1, -1, 1, 0}, false, false, false},
      {{8, 9, 10, 11}, {1, 0, -1, -1}, false, false, false},
      {{10, 11, 14, 15}, {1, -1, 1, -1}, false, false, false},
  };

  comparebinary(output, expected, variableTokens);
}

TEST_CASE("Test petrick for f(a, b)=Σm(0,1,2)") {
  vector<Token> variableTokens = {
      {TokenType::VAR, 'a'},
      {TokenType::VAR, 'b'},
  };

  vector<Implicant> implicant = {
      {{0, 1}, {0, -1}, false, false, false},
      {{0, 2}, {-1, 0}, false, false, false},
  };

  vector<Implicant> output = petrick(implicant);

  vector<Implicant> expected = {
      {{0, 1}, {0, -1}, false, false, false},
      {{0, 2}, {-1, 0}, false, false, false},
  };

  comparebinary(output, expected, variableTokens);
}

TEST_CASE(
    "Test petrick for f(a, b, c, d, e, "
    "f)=Σm(10,18,26,40,41,42,48,49,50,52,53,56,57,60,61)") {
  vector<Token> variableTokens = {
      {TokenType::VAR, 'a'}, {TokenType::VAR, 'b'}, {TokenType::VAR, 'c'},
      {TokenType::VAR, 'd'}, {TokenType::VAR, 'e'}, {TokenType::VAR, 'f'},
  };

  vector<Implicant> implicant = {
      {{10, 26}, {0, -1, 1, 0, 1, 0}, false, false, false},
      {{10, 42}, {-1, 0, 1, 0, 1, 0}, false, false, false},
      {{18, 26}, {0, 1, -1, 0, 1, 0}, false, false, false},
      {{18, 50}, {-1, 1, 0, 0, 1, 0}, false, false, false},
      {{40, 42}, {1, 0, 1, 0, -1, 0}, false, false, false},
      {{48, 50}, {1, 1, 0, 0, -1, 0}, false, false, false},
      {{40, 41, 56, 57}, {1, -1, 1, 0, 0, -1}, false, false, false},
      {{48, 49, 52, 53, 56, 57, 60, 61},
       {1, 1, -1, -1, 0, -1},
       false,
       false,
       false},
  };

  vector<Implicant> output = petrick(implicant);

  vector<Implicant> expected = {
      {{40, 41, 56, 57}, {1, -1, 1, 0, 0, -1}, false, false, false},
      {{10, 42}, {-1, 0, 1, 0, 1, 0}, false, false, false},
      {{18, 50}, {-1, 1, 0, 0, 1, 0}, false, false, false},
      {{10, 26}, {0, -1, 1, 0, 1, 0}, false, false, false},
      {{48, 49, 52, 53, 56, 57, 60, 61},
       {1, 1, -1, -1, 0, -1},
       false,
       false,
       false},
  };

  comparebinary(output, expected, variableTokens);
}