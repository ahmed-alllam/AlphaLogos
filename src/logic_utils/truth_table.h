#ifndef TRUTH_TABLE_H
#define TRUTH_TABLE_H

#include <iostream>
#include <string>
#include <stack>
#include <cctype>
#include <unordered_map>
#include <map>
#include <vector>
#include <set>

using namespace std;

map<int, char> variables;

bool isOperator(char c);
int getPrecedence(char op);
double applyOperation(double a, double b, char op);
double evaluateExpression(const std::string& expression);
string replaceVariables(const string& expression, unordered_map<char, bool> variableValues);
void expressionIterator(int num_var, string expression, unordered_map<char, bool> variableValues);
unordered_map<char, bool> countUniqueVariables(const string& expression);
map<int, char> uniqueVariablesIndex(const string& expression);
void truthTable();

#endif // TRUTH_TABLE_H
