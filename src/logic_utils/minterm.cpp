#include "minterm.h"

#include <string>
#include <vector>

#include "token.h"

using namespace std;

string mintermToString(Minterm minterm, vector<Token> uniqueVariables) {
  string mintermString = "";

  for (int i = 0; i < minterm.binary.size(); i++) {
    if (minterm.binary[i] == 1) {
      mintermString += string(1, uniqueVariables[i].value);
    } else {
      mintermString += string(1, uniqueVariables[i].value) + "'";
    }
  }

  return mintermString;
}
