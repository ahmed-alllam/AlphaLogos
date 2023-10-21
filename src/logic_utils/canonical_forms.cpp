#include <algorithm>
#include <iostream>
#include <stack>
#include <string>
#include <vector>
using namespace std;
#include "truth_table_generator.cpp"

vector<Token> unique(vector<Token> expression) {
  vector<Token> answer;
  for (int i = 0; i < expression.size(); i++) {
    if (expression[i].type == TokenType::VAR) {
      for (int j = 0; j < i; j++) {
        if (expression[i].value == expression[j].value) {
          break;
        }
      }
      answer.push_back(expression[i]);
    }
  }
  return answer;
}

vector<Token> canonical_forms_sop(string expression) {
  vector<vector<bool>> truth_table = generateTruthTable(expression);
  vector<Token> tokenized_string = tokenize(expression);
  vector<Token> uniqueVariables = unique(tokenized_string);
  vector<Token> canonical_sop;

  // Iterate through each row in the truth table
  for (size_t i = 0; i < truth_table.size(); i++) {
    vector<bool> row = truth_table[i];

    // Check if the row satisfies the expression
    if (row[row.size() - 1] == 1) {
      Token openBracket;
      openBracket.type = TokenType::OPEN_PAR;
      canonical_sop.push_back(openBracket);

      for (size_t j = 0; j < row.size() - 1; j++) {
        if (row[j]) {
          Token minterm_expression;
          minterm_expression.type = TokenType::VAR;
          minterm_expression.value = uniqueVariables[j].value;
          canonical_sop.push_back(minterm_expression);

          Token and_expression;
          and_expression.type = TokenType::AND;
          canonical_sop.push_back(and_expression);
        } else {
          Token not_expression;
          not_expression.type = TokenType::NOT_POST;

          Token variable_char;
          variable_char.type = TokenType::VAR;
          variable_char.value = uniqueVariables[j].value;

          canonical_sop.push_back(variable_char);
          canonical_sop.push_back(not_expression);

          Token and_expression;
          and_expression.type = TokenType::AND;
          canonical_sop.push_back(and_expression);
        }
      }

      // Remove the trailing AND operator
      canonical_sop.pop_back();

      Token closedBracket;
      closedBracket.type = TokenType::CLOSE_PAR;
      canonical_sop.push_back(closedBracket);

      Token or_expression;
      or_expression.type = TokenType::OR;
      canonical_sop.push_back(or_expression);
    }
  }

  // Remove the trailing OR operator
  canonical_sop.pop_back();

  return canonical_sop;
}

vector<Token> canonical_forms_pos(string expression) {
  vector<vector<bool>> truth_table = generateTruthTable(expression);
  vector<Token> tokenized_string = tokenize(expression);
  vector<Token> uniqueVariables = unique(tokenized_string);
  vector<Token> canonical_pos;

  // Iterate through each row in the truth table
  for (size_t i = 0; i < truth_table.size(); i++) {
    vector<bool> row = truth_table[i];

    // Check if the row satisfies the expression
    if (row[row.size() - 1] == 0) {
      Token openBracket;
      openBracket.type = TokenType::OPEN_PAR;
      canonical_pos.push_back(openBracket);
      for (size_t j = 0; j < row.size() - 1; j++) {
        if (!row[j]) {
          Token minterm_expression;
          minterm_expression.type = TokenType::VAR;
          minterm_expression.value = uniqueVariables[j].value;
          canonical_pos.push_back(minterm_expression);

          Token or_expression;
          or_expression.type = TokenType::OR;
          canonical_pos.push_back(or_expression);
        } else {
          Token not_expression;
          not_expression.type = TokenType::NOT_POST;

          Token variable_char;
          variable_char.type = TokenType::VAR;
          variable_char.value = uniqueVariables[j].value;

          canonical_pos.push_back(variable_char);
          canonical_pos.push_back(not_expression);

          Token or_expression;
          or_expression.type = TokenType::OR;
          canonical_pos.push_back(or_expression);
        }
      }

      canonical_pos.pop_back();

      Token closedBracket;
      closedBracket.type = TokenType::CLOSE_PAR;
      canonical_pos.push_back(closedBracket);

      Token and_expression;
      and_expression.type = TokenType::AND;
      canonical_pos.push_back(and_expression);
    }
  }

  canonical_pos.pop_back();

  return canonical_pos;
}

int main() {
  std::string expression = "a + b + c";
  std::vector<Token> canonical = canonical_forms_sop(expression);

  // Display the canonical forms
  std::cout << "Canonical Forms:\n";
  for (const Token& token : canonical) {
    if (token.type == TokenType::VAR)
      std::cout << token.value;
    else if (token.type == TokenType::NOT_POST)
      std::cout << "\'";
    else if (token.type == TokenType::AND)
      std::cout << "*";
    else if (token.type == TokenType::OR)
      std::cout << "+";
    else if (token.type == TokenType::CLOSE_PAR)
      std::cout << ")";
    else if (token.type == TokenType::OPEN_PAR)
      std::cout << "(";
    std::cout << " ";
  }
  std::cout << std::endl;

  return 0;
}