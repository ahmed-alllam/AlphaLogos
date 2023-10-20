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
      case '!':
        token.type = TokenType::NOT_PRE;
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

        throw "Invalid character in expression";
    }

    tokens.push_back(token);
  }

  return tokens;
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
  int starting_copy = index;

  bool value;

  if (index >= tokens.size()) {
    throw "Unexpected end of expression";
  }

  const Token &token = tokens[index];

  switch (token.type) {
    case TokenType::VAR:
      for (const auto &[varToken, varValue] : permutation) {
        if (varToken == token) {
          value = varValue;
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

    case TokenType::NOT_PRE:
      index++;  // Skip '!'
      value = !evaluateExpression(
          tokens, index, permutation);  // Recurse for the negated value
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
    value = value | nextValue;
  }

  return value;
}

vector<vector<bool>> generateTruthTable(string expression) {
  vector<Token> tokens = tokenize(expression);
  vector<vector<pair<Token, bool>>> permutations = generatePermutations(tokens);
  vector<vector<bool>> truthTable;

  for (auto permutation : permutations) {
    vector<bool> row;

    // add permutation values to row acsending by as they were stored in the map
    for (const auto &[token, value] : permutation) {
      row.push_back(value);
    }

    int index = 0;

    row.push_back(evaluateExpression(tokens, index, permutation));
    truthTable.push_back(row);
  }

  return truthTable;
}