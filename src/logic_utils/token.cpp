#include "token.h"

#include <string>
#include <vector>

using namespace std;

vector<Token> tokenize(string expression) {
  vector<Token> tokens;

  for (int i = 0; i < expression.length(); i++) {
    char c = expression[i];

    if (c == ' ') {
      continue;
    }

    Token token;

    switch (c) {
      case '*':
        token.type = TokenType::AND;
        break;
      case '+':
        token.type = TokenType::OR;
        break;
      case '\'':
        token.type = TokenType::NOT_POST;
        break;
      case '(':
        token.type = TokenType::OPEN_PAR;
        break;
      case ')':
        token.type = TokenType::CLOSE_PAR;
        break;
      default:
        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
          token.type = TokenType::VAR;
          token.value = c;
          break;
        }

        throw("Invalid character in expression");
    }

    tokens.push_back(token);
  }

  return tokens;
}

vector<Token> getUniqueVariables(vector<Token> tokens) {
  vector<Token> uniqueVariables;

  for (Token token : tokens) {
    if (token.type == TokenType::VAR) {
      bool found = false;

      for (Token uniqueVariable : uniqueVariables) {
        if (uniqueVariable.value == token.value) {
          found = true;
          break;
        }
      }

      if (!found) {
        uniqueVariables.push_back(token);
      }
    }
  }

  return uniqueVariables;
}
