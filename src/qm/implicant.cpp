#include "implicant.h"

#include <algorithm>
#include <vector>

#include "../logic_utils/token.h"

using namespace std;

string implicantToString(const Implicant &implicant,
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
