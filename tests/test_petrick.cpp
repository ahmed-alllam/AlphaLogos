#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include <vector>

#include "../src/logic_utils/minterm.h"
#include "../src/logic_utils/token.h"
#include "../src/qm/implicant.h"
#include "../src/qm/petrick.h"
#include "../src/qm/prime_implicants.h"

void compareImplicants(const vector<Implicant>& output,
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

  compareImplicants(output, expected, variableTokens);
}