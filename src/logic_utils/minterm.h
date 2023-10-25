#ifndef MINTERM_H
#define MINTERM_H

#include <string>
#include <vector>

#include "token.h"

using namespace std;

struct Minterm {
  int index;  // index in the truth table
  vector<int> binary;
  int num_ones;
  bool is_covered;
};

string mintermToString(Minterm minterm, vector<Token> uniqueVariables);

string canonicalSoPToString(vector<Minterm> minterms,
                            vector<Token> uniqueVariables);

#endif  // MINTERM_H