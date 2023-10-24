#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <vector>

using namespace std;

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

vector<Token> getUniqueVariables(vector<Token> tokens);

#endif  // TOKEN_H