#include "canonical_forms.h"

#include <algorithm>
#include <iostream>
#include <stack>
#include <string>
#include <vector>

#include "maxterm.h"
#include "minterm.h"
#include "token.h"

using namespace std;

vector<Minterm> generateMinTerms(vector<Token> uniqueVariables,
                                 vector<vector<bool>> truthTable) {
  vector<Minterm> canonicalSoP;

  for (int i = 0; i < truthTable.size(); i++) {
    vector<bool> row = truthTable[i];

    if (row[row.size() - 1] == true) {
      Minterm minterm;
      minterm.index = i;
      minterm.is_covered = false;

      int num_ones = 0;
      for (int j = 0; j < row.size() - 1; j++) {
        if (row[j] == true) {
          num_ones++;
        }

        minterm.binary.push_back(row[j]);
      }

      minterm.num_ones = num_ones;

      canonicalSoP.push_back(minterm);
    }
  }

  return canonicalSoP;
}

vector<Maxterm> generateMaxTerms(vector<Token> uniqueVariables,
                                 vector<vector<bool>> truthTable) {
  vector<Maxterm> canonicalPoS;

  for (int i = 0; i < truthTable.size(); i++) {
    vector<bool> row = truthTable[i];

    if (row[row.size() - 1] == false) {
      Maxterm maxterm;
      maxterm.index = i;
      maxterm.is_covered = false;

      for (int j = 0; j < row.size() - 1; j++) {
        maxterm.binary.push_back(row[j]);
      }

      canonicalPoS.push_back(maxterm);
    }
  }

  return canonicalPoS;
}
