

#include <cassert>
#include <deque>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

void printTokens(deque<string> tokens);

bool str2Bool(string toConvert);

string bool2Str(bool toConvert);

string subString(string str, int index0, int index1);

string evaluate(string var0, string var1, string lop, unordered_map<string, bool> valueMap);

bool solveEquationDeque(deque<string> equationTokens, unordered_map<string, bool> valueMap);

deque<string> tokenizeSpaces(string rawStr);

int getEndBracketPosition(string eqn, int firstBracketPosition);

bool solveEquation(string eqn, unordered_map<string, bool> valueMap);

string extractVariables(const string &expression);

string addSpaceAfterVariables(const string &expression);

bool truth_table_generator(string expression);

