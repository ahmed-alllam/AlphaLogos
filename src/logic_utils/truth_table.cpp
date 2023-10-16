#include <iostream>

#include <string>

#include <stack>

#include <cctype>

#include <unordered_map>
#include <map>
#include <vector>

#include <set>

using namespace std;


map < int, char > variables;



bool isOperator(char c) {
return c == '+' || c == '*' || c == '~' || c == '!';
}

int getPrecedence(char op) {
  if (op == '+')
    return 1;
  if (op == '*')
    return 2;
  return 0;
}

double applyOperation(double a, double b, char op) {
  switch (op) {
  case '+':
    return a || b;
  case '*':
    return a && b;
  default:
    return 0.0; // Invalid operator
  }
}

double evaluateExpression(const std::string & expression) {
  std::stack < double > values;
  std::stack < char > operators;

  for (size_t i = 0; i < expression.length(); ++i) {
    char c = expression[i];

    if (isspace(c))
      continue;

    if (isdigit(c)) {
      std::string num;
      while (i < expression.length() && (isdigit(expression[i]) || expression[i] == '.')) {
        num += expression[i];
        ++i;
      }
      --i;
      values.push(std::stod(num));
    } else if (c == '(') {
      operators.push(c);
    } else if (c == ')') {
      while (!operators.empty() && operators.top() != '(') {
        double b = values.top();
        values.pop();

        double a = values.top();
        values.pop();

        char op = operators.top();
        operators.pop();

        values.push(applyOperation(a, b, op));
      }

      if (!operators.empty())
        operators.pop(); // Discard the opening parenthesis
    } else if (isOperator(c)) {
      while (!operators.empty() && getPrecedence(c) <= getPrecedence(operators.top())) {
        double b = values.top();
        values.pop();

        double a = values.top();
        values.pop();

        char op = operators.top();
        operators.pop();

        values.push(applyOperation(a, b, op));
      }

      operators.push(c);
    }
  }

  while (!operators.empty()) {
    double b = values.top();
    values.pop();

    double a = values.top();
    values.pop();

    char op = operators.top();
    operators.pop();

    values.push(applyOperation(a, b, op));
  }
  cout << values.top() << endl;
  return values.top();
}



string replaceVariables(const string & expression, unordered_map < char, bool > variableValues) {
  string result;
  for (char token: expression) {
    if (isalpha(token)) {
      // If the token is a variable, append the corresponding value (0 or 1) to the result string
      result += variableValues[token] ? '1' : '0';
    } else {
      // If the token is not a variable, append it as it is
      result += token;
    }
  }
  return result;
}

void expressionIterator(int num_var, string expression, unordered_map < char, bool > variableValues) {
  if (num_var == 0) {
    expression = replaceVariables(expression, variableValues);
    evaluateExpression(expression);
  } else {
    variableValues[variables[num_var-1]] = 0;
    expressionIterator(num_var - 1, expression, variableValues);
    variableValues[variables[num_var-1]] = 1;
    expressionIterator(num_var - 1, expression, variableValues);
  }
}

unordered_map < char, bool > countUniqueVariables(const string & expression) {
  unordered_map < char, bool > variables;

  for (char token: expression) {
    if (isalpha(token)) {
      variables[token] = 0;
    }
  }
  return variables;
}

map<int,char> uniqueVariablesIndex(const string & expression) {
  map<int,char> variables;
  int i = 0;
  for (char token: expression) {
    if (isalpha(token)) {
      variables.insert(make_pair(i,token));
      i++;
    }
  }
  return variables;
}

void truth table(){
  std::string expression;
  std::cout << "Enter the mathematical expression: ";
  std::getline(std::cin, expression);
  unordered_map < char, bool > variableValues = countUniqueVariables(expression);
  cout << variableValues.size() << endl;
  variables = uniqueVariablesIndex(expression);
  for(int i = 0;i<variables.size();i++){
    cout << variables[i] << endl;
  }
  expressionIterator(variableValues.size(), expression, variableValues);
}
