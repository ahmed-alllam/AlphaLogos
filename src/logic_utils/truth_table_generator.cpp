#include <string>
#include <unordered_map>
#include <unordered_set>
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

vector<unordered_map<Token, bool>> generatePermutations(
    const vector<Token> &tokens) {
  vector<unordered_map<Token, bool>> permutations;

  unordered_set<char> uniqueVarValues;
  vector<Token> uniqueVarTokens;

  for (const auto &token : tokens) {
    if (token.type == TokenType::VAR &&
        uniqueVarValues.find(token.value) == uniqueVarValues.end()) {
      uniqueVarValues.insert(token.value);
      uniqueVarTokens.push_back(token);
    }
  }

  int numUniqueVars = uniqueVarTokens.size();

  for (int i = 0; i < pow(2, numUniqueVars); i++) {
    int temp = i;
    unordered_map<Token, bool> permutation;
    for (const auto &uniqueToken : uniqueVarTokens) {
      permutation[uniqueToken] = temp % 2 == 0;
      temp /= 2;
    }

    permutations.push_back(permutation);
  }

  return permutations;
}

bool evaluateExpression(const vector<Token> &tokens, int index,
                        const unordered_map<Token, bool> &permutation) {
  bool value;

  if (index >= tokens.size()) {
    throw "Unexpected end of expression";
  }

  const Token &token = tokens[index];

  switch (token.type) {
    case TokenType::VAR:
      // Look up the value of the variable in the permutation by matching the
      // token
      for (const auto &[permToken, permValue] : permutation) {
        if (permToken.value == token.value) {
          value = permValue;
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

  // Look for AND (*) or implicit multiplication by juxtaposition
  while (index < tokens.size() && (tokens[index].type == TokenType::AND ||
                                   tokens[index].type == TokenType::OPEN_PAR)) {
    if (tokens[index].type == TokenType::AND) {
      index++;  // Skip '*'
    }
    value = value && evaluateExpression(tokens, index, permutation);
  }

  // Look for OR (+)
  while (index < tokens.size() && tokens[index].type == TokenType::OR) {
    index++;  // Skip '+'
    value = value || evaluateExpression(tokens, index, permutation);
  }

  return value;
}

vector<vector<bool>> generateTruthTable(string expression) {
  vector<Token> tokens = tokenize(expression);
  vector<unordered_map<Token, bool>> permutations =
      generatePermutations(tokens);
  vector<vector<bool>> truthTable;

  for (auto permutation : permutations) {
    vector<bool> row;
    for (int i = 0; i < tokens.size(); i++) {
      if (tokens[i].type == TokenType::VAR) {
        row.push_back(permutation[tokens[i]]);
      }
    }

    row.push_back(evaluateExpression(tokens, 0, permutation));
    truthTable.push_back(row);
  }

  return truthTable;
}