#include "maxterm.h"

#include <string>
#include <vector>

#include "token.h"

using namespace std;

string maxtermToString(Maxterm maxterm, vector<Token> uniqueVariables) {
  string maxtermString = "";

  for (int i = 0; i < maxterm.binary.size(); i++) {
    if (maxterm.binary[i] == 0) {
      maxtermString += string(1, uniqueVariables[i].value);
    } else {
      maxtermString += string(1, uniqueVariables[i].value) + "'";
    }

    if (i != maxterm.binary.size() - 1) {
      maxtermString += "+";
    }
  }

  return maxtermString;
}

string canonicalPoSToString(vector<Maxterm> maxterms,
                            vector<Token> uniqueVariables) {
  string maxtermsString = "";

  for (int i = 0; i < maxterms.size(); i++) {
    maxtermsString += "(" + maxtermToString(maxterms[i], uniqueVariables) + ")";
  }

  return maxtermsString;
}
