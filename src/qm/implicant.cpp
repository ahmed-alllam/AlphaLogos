#include "implicant.h"

#include <algorithm>
#include <vector>

#include "../logic_utils/token.h"

using namespace std;

string implicantToString(const Implicant& implicant,
                         vector<Token> variableTokens) {
  string result;

  for (int i = 0; i < implicant.binary.size(); i++) {
    if (implicant.binary[i] == 1) {
      result += string(1, variableTokens[i].value);
    } else if (implicant.binary[i] == 0) {
      result += string(1, variableTokens[i].value) + "'";
    } else {
      continue;
    }
  }

  return result;
}

ostream& operator<<(ostream& os, const Implicant& imp) {
  os << "{ Minterms: [";
  for (const auto& m : imp.minterms) {
    os << m << ",";
  }
  os << "], Binary: [";
  for (const auto& b : imp.binary) {
    os << b << ",";
  }
  os << "], is_prime: " << imp.is_prime;
  os << ", is_essential: " << imp.is_essential;
  os << ", is_checked: " << imp.is_checked << " }";
  return os;
}
