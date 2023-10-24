#ifndef MAXTERM_H
#define MAXTERM_H

#include <string>
#include <vector>

#include "token.h"

using namespace std;

struct Maxterm {
  int index;  // index in the truth table
  vector<int> binary;
  bool is_covered;
};

string maxtermToString(Maxterm maxterm, vector<Token> uniqueVariables);

#endif  // MAXTERM_H