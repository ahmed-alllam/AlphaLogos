#include <algorithm>
#include <stack>
#include <string>
#include <vector>

using namespace std;

#include "truth_table_generator.h"

vector<Token> tokenize(string expression) {
  vector<Token> tokens;

  for (size_t i = 0; i < expression.length(); i++) {
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

vector<Token> addParenthesesForPrecedence(vector<Token> tokens) {
  vector<Token> newTokens;
  int openParCount = 0;  // Track existing open parentheses
  int termStart = -1;    // Track the start of a term

  for (size_t i = 0; i < tokens.size(); i++) {
    const auto &token = tokens[i];

    if (token.type == TokenType::OPEN_PAR) {
      openParCount++;
    } else if (token.type == TokenType::CLOSE_PAR) {
      openParCount--;
    }

    if (termStart == -1 &&
        (token.type == TokenType::VAR || token.type == TokenType::NOT_POST)) {
      termStart = i;  // Mark the start of a term
    }

    // Check if we've reached the end of a term
    bool endOfTerm =
        (i + 1 == tokens.size() || tokens[i + 1].type == TokenType::OR);
    if (endOfTerm && openParCount == 0 && termStart != -1) {
      if (termStart == 0 || tokens[termStart - 1].type != TokenType::OPEN_PAR) {
        newTokens.push_back({TokenType::OPEN_PAR, '('});
      }
      for (int j = termStart; j <= i; j++) {
        newTokens.push_back(tokens[j]);
      }
      if (i == tokens.size() - 1 || tokens[i].type != TokenType::CLOSE_PAR) {
        newTokens.push_back({TokenType::CLOSE_PAR, ')'});
      }
      termStart = -1;  // Reset term start
    } else if (termStart == -1) {
      newTokens.push_back(token);  // Add non-term tokens directly
    }
  }

  return newTokens;
}

vector<vector<pair<Token, bool>>> generatePermutations(
    const vector<Token> &tokens) {
  vector<vector<pair<Token, bool>>> permutations;

  vector<Token> uniqueVarTokens;

  for (const auto &token : tokens) {
    if (token.type == TokenType::VAR &&
        find(uniqueVarTokens.begin(), uniqueVarTokens.end(), token) ==
            uniqueVarTokens.end()) {
      uniqueVarTokens.push_back(token);
    }
  }

  int numUniqueVars = uniqueVarTokens.size();

  for (int i = 0; i < (1 << numUniqueVars); i++) {
    int temp = i;
    vector<pair<Token, bool>> permutation;
    for (const auto &uniqueToken : uniqueVarTokens) {
      permutation.push_back({uniqueToken, temp % 2});
      temp /= 2;
    }

    permutations.push_back(permutation);
  }

  return permutations;
}

bool evaluateExpression(const vector<Token> &tokens, int &index,
                        const vector<pair<Token, bool>> &permutation) {
  bool value;

  if (index >= tokens.size()) {
    throw "Unexpected end of expression";
  }

  const Token &token = tokens[index];

  switch (token.type) {
    case TokenType::VAR:
      for (const auto &pair : permutation) {
        if (pair.first == token) {
          value = pair.second;
          break;
        }
      }

      index++;
      break;

    case TokenType::OPEN_PAR:
      index++;  // Skip '('
      value = evaluateExpression(
          tokens, index, permutation);  // Recurse for the inner expression

      if (index >= tokens.size() ||
          tokens[index].type != TokenType::CLOSE_PAR) {
        throw "Unmatched parentheses";
      }
      index++;  // Skip ')'
      break;
    default:
      throw "Unexpected token in expression";
  }

  // Postfix NOT (e.g., A')
  if (index < tokens.size() && tokens[index].type == TokenType::NOT_POST) {
    value = !value;
    index++;
  }

  // Handle implicit multiplication and explicit AND
  while (index < tokens.size() && (tokens[index].type == TokenType::VAR ||
                                   tokens[index].type == TokenType::OPEN_PAR ||
                                   tokens[index].type == TokenType::AND)) {
    if (tokens[index].type == TokenType::AND) {
      index++;  // Skip '*'
    }
    bool nextValue = evaluateExpression(tokens, index, permutation);
    value = value & nextValue;
  }

  // Handle OR
  while (index < tokens.size() && tokens[index].type == TokenType::OR) {
    index++;  // Skip '+'
    bool nextValue = evaluateExpression(tokens, index, permutation);
    value |= nextValue;
  }

  return value;
}

vector<vector<bool>> generateTruthTable(string expression) {
  vector<Token> tokens = tokenize(expression);
  tokens = addParenthesesForPrecedence(tokens);
  vector<vector<pair<Token, bool>>> permutations = generatePermutations(tokens);
  vector<vector<bool>> truthTable;

  for (auto permutation : permutations) {
    vector<bool> row;

    for (const auto &pair : permutation) {
      row.push_back(pair.second);
    }

    int index = 0;

    row.push_back(evaluateExpression(tokens, index, permutation));
    truthTable.push_back(row);
  }

  return truthTable;
}