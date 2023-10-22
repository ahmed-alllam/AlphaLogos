#ifndef TRUTH_TABLE_GENERATOR_H
#define TRUTH_TABLE_GENERATOR_H

#include <string>
#include <utility>
#include <vector>

using namespace std;

// Todo: put this in a separate file, as it is used in multiple places
enum class TokenType {
  VAR,       // a, b, c, ...
  AND,       // *
  OR,        // +
  NOT_POST,  // '
  OPEN_PAR,  // (
  CLOSE_PAR  // )
};

struct Token {
  TokenType type;
  char value;  // only for VAR

  bool operator==(const Token &other) const {
    return type == other.type && value == other.value;
  }
};

vector<Token> tokenize(string expression);

vector<Token> addParenthesesForPrecedence(vector<Token> tokens);

vector<vector<pair<Token, bool>>> generatePermutations(
    const vector<Token> &tokens);

bool evaluateExpression(const vector<Token> &tokens, int &index,
                        const vector<pair<Token, bool>> &permutation);

vector<vector<bool>> generateTruthTable(string expression);

#endif