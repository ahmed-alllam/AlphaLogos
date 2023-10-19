#ifndef TRUTH_TABLE_GENERATOR_H
#define TRUTH_TABLE_GENERATOR_H

#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

enum class TokenType {
  VAR,       // a, b, c, ...
  AND,       // *
  OR,        // +
  NOT_PRE,   // !
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

namespace std {
template <>
struct hash<Token> {
  size_t operator()(const Token &token) const {
    return hash<int>()(static_cast<int>(token.type)) ^
           hash<char>()(token.value);
  }
};
}  // namespace std

vector<Token> tokenize(string expression);

vector<unordered_map<Token, bool>> generatePermutations(
    const vector<Token> &tokens);

bool evaluateExpression(const vector<Token> &tokens, int index,
                        const unordered_map<Token, bool> &permutation);

vector<vector<bool>> generateTruthTable(string expression);

#endif