#ifndef PRIME_IMPLICANTS_H
#define PRIME_IMPLICANTS_H

#include <string>
#include <algorithm>
#include <vector>

#include "../logic_utils/truth_table_generator.h"

using namespace std;

struct Implicant {
  vector<int> minterms;
  vector<int> binary;
  bool is_prime;
  bool is_essential;
  bool is_checked;

  bool operator==(const Implicant &other) const {
    if (minterms.size() != other.minterms.size()) {
      return false;
    }

    vector<int> minterms = this->minterms;
    vector<int> other_minterms = other.minterms;

    sort(minterms.begin(), minterms.end());
    sort(other_minterms.begin(), other_minterms.end());

    for (int i = 0; i < minterms.size(); i++) {
      if (minterms[i] != other_minterms[i]) {
        return false;
      }
    }

    return true;
  }
};

// temporary struct for minterms. should be removed later, and put in
// truth_table_generator.h
struct Minterm {
  int index;  // index in the truth table
  vector<int> binary;
  int num_ones;
  bool is_covered;
};

vector<Implicant> generatePrimeImplicants(vector<Minterm> minterms);

// temporary function. should be removed later, should be put in a seperate file
// as it's used in multiple files
string implicantToString(const Implicant &implicant,
                         vector<Token> variableTokens);

#endif  // PRIME_IMPLICANTS_H
