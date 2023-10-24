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

string mintermsToString(vector<Minterm> minterms,
                        vector<Token> uniqueVariables) {
  string mintermsString = "";

  for (int i = 0; i < minterms.size(); i++) {
    mintermsString += mintermToString(minterms[i], uniqueVariables);

    if (i != minterms.size() - 1) {
      mintermsString += "+";
    }
  }

  return mintermsString;
}