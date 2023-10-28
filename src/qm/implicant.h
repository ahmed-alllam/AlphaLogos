#ifndef IMPLICANT_H
#define IMPLICANT_H

#include <algorithm>
#include <vector>

#include "../logic_utils/token.h"

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

string implicantToString(const Implicant &implicant,
                         vector<Token> variableTokens);

#endif  // IMPLICANT_H