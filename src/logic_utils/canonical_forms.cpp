#include <algorithm>
#include <iostream>
#include <stack>
#include <string>
#include <vector>
using namespace std;
#include "truth_table_generator.cpp"

// Function to find unique variables in the expression
vector<Token> unique(vector<Token> expression) {
  vector<Token> answer;
  for (int i = 0; i < expression.size(); i++) {
    if (expression[i].type == TokenType::VAR) {
      // Check if the variable already exists in the answer vector
      for (int j = 0; j < i; j++) {
        if (expression[i].value == expression[j].value) {
          break;
        }
      }
      // Add the unique variable to the answer vector
      answer.push_back(expression[i]);
    }
  }
  return answer;
}

// Function to generate the canonical SOP (Sum of Products) form
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

      // Iterate through each variable in the row
      for (size_t j = 0; j < row.size() - 1; j++) {
        if (row[j]) {
          // Variable is true, add it to the SOP as is
          Token minterm_expression;
          minterm_expression.type = TokenType::VAR;
          minterm_expression.value = uniqueVariables[j].value;
          canonical_sop.push_back(minterm_expression);

          Token and_expression;
          and_expression.type = TokenType::AND;
          canonical_sop.push_back(and_expression);
        } else {
          // Variable is false, add its negation to the SOP
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

// Function to generate the canonical POS (Product of Sums) form
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

      // Iterate through each variable in the row
      for (size_t j = 0; j < row.size() - 1; j++) {
        if (!row[j]) {
          // Variable is false, add it to the POS as is
          Token minterm_expression;
          minterm_expression.type = TokenType::VAR;
          minterm_expression.value = uniqueVariables[j].value;
          canonical_pos.push_back(minterm_expression);

          Token or_expression;
          or_expression.type = TokenType::OR;
          canonical_pos.push_back(or_expression);
        } else {
          // Variable is true, add its negation to the POS
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

      // Remove the trailing OR operator
      canonical_pos.pop_back();

      Token closedBracket;
      closedBracket.type = TokenType::CLOSE_PAR;
      canonical_pos.push_back(closedBracket);

      Token and_expression;
      and_expression.type = TokenType::AND;
      canonical_pos.push_back(and_expression);
    }
  }

  // Remove the trailing AND operator
  canonical_pos.pop_back();

  return canonical_pos;
}
