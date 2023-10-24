#ifndef TRUTH_TABLE_GENERATOR_H
#define TRUTH_TABLE_GENERATOR_H

#include <string>
#include <utility>
#include <vector>

#include "token.h"

using namespace std;

vector<Token> addParenthesesForPrecedence(vector<Token> tokens);

vector<vector<pair<Token, bool>>> generatePermutations(
    const vector<Token> &tokens);

bool evaluateExpression(const vector<Token> &tokens, int &index,
                        const vector<pair<Token, bool>> &permutation);

vector<vector<bool>> generateTruthTable(vector<Token> tokens);

#endif