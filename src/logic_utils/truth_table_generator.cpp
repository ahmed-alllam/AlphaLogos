#include <algorithm>
#include <stack>
#include <string>
#include <vector>

using namespace std;

#include "truth_table_generator.h"

vector<Token> addParenthesesForPrecedence(vector<Token> tokens) {
  std::vector<Token> newTokens;
  std::vector<Token> term;
  int openParCount = 0;

  for (size_t i = 0; i < tokens.size(); i++) {
    Token token = tokens[i];
    if (token.type == TokenType::OPEN_PAR) {
      openParCount++;
    } else if (token.type == TokenType::CLOSE_PAR) {
      openParCount--;
    }

    if (openParCount == 0 && token.type == TokenType::OR) {
      if (!term.empty()) {
        // Don't add extra parentheses if the term is already enclosed in
        // parentheses
        if (term.front().type == TokenType::OPEN_PAR &&
            term.back().type == TokenType::CLOSE_PAR) {
          newTokens.insert(newTokens.end(), term.begin(), term.end());
        } else {
          newTokens.push_back({TokenType::OPEN_PAR, '('});
          newTokens.insert(newTokens.end(), term.begin(), term.end());
          newTokens.push_back({TokenType::CLOSE_PAR, ')'});
        }
        term.clear();  // Reset term
      }

      // Add OR to newTokens
      newTokens.push_back(token);
    } else {
      term.push_back(token);
    }

    // Handle the last token
    if (i == tokens.size() - 1 && !term.empty()) {
      if (term.front().type == TokenType::OPEN_PAR &&
          term.back().type == TokenType::CLOSE_PAR) {
        newTokens.insert(newTokens.end(), term.begin(), term.end());
      } else {
        newTokens.push_back({TokenType::OPEN_PAR, '('});
        newTokens.insert(newTokens.end(), term.begin(), term.end());
        newTokens.push_back({TokenType::CLOSE_PAR, ')'});
      }
    }
  }

  return newTokens;
}

vector<vector<pair<Token, bool>>> generatePermutations(
    const vector<Token> &tokens) {
  vector<vector<pair<Token, bool>>> permutations;

  vector<Token> uniqueVarTokens = getUniqueVariables(tokens);

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

  // Postfix NOT (e.g., A'). Handle multiple NOTs
  while (index < tokens.size() && tokens[index].type == TokenType::NOT_POST) {
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

vector<vector<bool>> generateTruthTable(vector<Token> tokens) {
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