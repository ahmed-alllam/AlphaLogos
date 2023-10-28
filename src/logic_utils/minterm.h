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

  bool operator==(Minterm& other) {
    if (index != other.index || binary != other.binary ||
        num_ones != other.num_ones) {
      return false;
    }

    return true;
  }
};

string mintermToString(Minterm minterm, vector<Token> uniqueVariables);

string canonicalSoPToString(vector<Minterm> minterms,
                            vector<Token> uniqueVariables);

#endif  // MINTERM_H