#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include <vector>

#include "../src/logic_utils/minterm.h"
#include "../src/logic_utils/token.h"
#include "../src/qm/essential_prime_implicants.h"
#include "../src/qm/implicant.h"
#include "../src/qm/petrick.h"
#include "../src/qm/prime_implicants.h"
#include "../src/qm/uncovered_minterms.h"

using namespace std;

void comparebinary(const vector<Implicant> &output,
                   const vector<Implicant> &expected,
                   vector<Token> variableTokens) {
  REQUIRE(output.size() == output.size());

  // find the implicant in output that matches the implicant in expected
  for (const auto &expected_implicant : expected) {
    bool found = false;
    for (const auto &output_implicant : output) {
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

  vector<Minterm> minterms = {
      {0, {0, 0, 0, 0}, 0, false},  {1, {0, 0, 0, 1}, 1, false},
      {2, {0, 0, 1, 0}, 1, false},  {4, {0, 1, 0, 0}, 1, false},
      {6, {0, 1, 1, 0}, 2, false},  {8, {1, 0, 0, 0}, 1, false},
      {9, {1, 0, 0, 1}, 2, false},  {11, {1, 0, 1, 1}, 3, false},
      {13, {1, 1, 0, 1}, 3, false}, {15, {1, 1, 1, 1}, 4, false},
  };

  vector<Implicant> implicants = generatePrimeImplicants(minterms);

  vector<Implicant> EPIs = generateEssentialPrimeImplicants(implicants);

  vector<Minterm> uncoveredMinterms = getUncoveredMinterms(minterms, EPIs);

  vector<Implicant> output =
      doPetrickMinimization(implicants, EPIs, uncoveredMinterms);

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

  vector<Minterm> minterms = {
      {2, {0, 0, 1, 0}, 1, false},  {6, {0, 1, 1, 0}, 2, false},
      {8, {1, 0, 0, 0}, 1, false},  {9, {1, 0, 0, 1}, 2, false},
      {10, {1, 0, 1, 0}, 2, false}, {11, {1, 0, 1, 1}, 3, false},
      {14, {1, 1, 1, 0}, 3, false}, {15, {1, 1, 1, 1}, 4, false},
  };

  vector<Implicant> implicant = generatePrimeImplicants(minterms);

  vector<Implicant> EPIs = generateEssentialPrimeImplicants(implicant);

  vector<Minterm> uncoveredMinterms = getUncoveredMinterms(minterms, EPIs);

  vector<Implicant> output =
      doPetrickMinimization(implicant, EPIs, uncoveredMinterms);

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

  vector<Minterm> minterms = {
      {0, {0, 0}, 0, false},
      {1, {0, 1}, 1, false},
      {2, {1, 0}, 1, false},
  };

  vector<Implicant> implicant = generatePrimeImplicants(minterms);

  vector<Implicant> EPIs = generateEssentialPrimeImplicants(implicant);

  vector<Minterm> uncoveredMinterms = getUncoveredMinterms(minterms, EPIs);

  vector<Implicant> output =
      doPetrickMinimization(implicant, EPIs, uncoveredMinterms);

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

  vector<Minterm> minterms = {
      {10, {0, 0, 1, 0, 1, 0}, 2, false}, {18, {0, 1, 0, 0, 1, 0}, 2, false},
      {26, {0, 1, 1, 0, 1, 0}, 3, false}, {40, {1, 0, 1, 0, 0, 0}, 2, false},
      {41, {1, 0, 1, 0, 0, 1}, 3, false}, {42, {1, 0, 1, 0, 1, 0}, 3, false},
      {48, {1, 1, 0, 0, 0, 0}, 2, false}, {49, {1, 1, 0, 0, 0, 1}, 3, false},
      {50, {1, 1, 0, 0, 1, 0}, 3, false}, {52, {1, 1, 0, 1, 0, 0}, 3, false},
      {53, {1, 1, 0, 1, 0, 1}, 4, false}, {56, {1, 1, 1, 0, 0, 0}, 3, false},
      {57, {1, 1, 1, 0, 0, 1}, 4, false}, {60, {1, 1, 1, 1, 0, 0}, 4, false},
      {61, {1, 1, 1, 1, 0, 1}, 5, false},
  };

  vector<Implicant> PI = generatePrimeImplicants(minterms);

  INFO("PIs.size() = ");
  INFO(PI.size());

  vector<Implicant> EPIs = generateEssentialPrimeImplicants(PI);

  INFO("EPIs.size() = ");
  INFO(EPIs.size());

  vector<Minterm> uncoveredMinterms = getUncoveredMinterms(minterms, EPIs);
  INFO("uncoveredMinterms.size() = ");
  INFO(uncoveredMinterms.size());

  vector<Implicant> output = doPetrickMinimization(PI, EPIs, uncoveredMinterms);
  INFO("ouput.size() = ");
  INFO(output.size());

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