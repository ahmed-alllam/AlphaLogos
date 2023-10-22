#include "kmap.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "../logic_utils/truth_table_generator.h"
#include "../qm/prime_implicants.h"

using namespace std;

vector<string> generateGrayCode(int n) {
  if (n == 0) return {""};
  if (n == 1) return {"0", "1"};

  vector<string> previous = generateGrayCode(n - 1);
  vector<string> current;

  for (const auto& str : previous) {
    current.push_back("0" + str);
  }
  for (auto it = previous.rbegin(); it != previous.rend(); ++it) {
    current.push_back("1" + *it);
  }

  return current;
}

int binaryToGray(int num) { return num ^ (num >> 1); }

int calculateMinterm(int row, int col, int numCols) {
  int grayRow = binaryToGray(row);
  int grayCol = binaryToGray(col);
  return grayRow * numCols + grayCol;
}

vector<vector<string>> makeKMap(vector<Implicant> primeImplicants,
                                vector<Token> variableTokens,
                                vector<Minterm> minterms) {
  if (variableTokens.size() < 2 || variableTokens.size() > 4) {
    throw "Invalid number of variables for KMap.";
  }

  int numRows = 1 << (variableTokens.size() / 2);
  int numCols = 1 << (variableTokens.size() - variableTokens.size() / 2);

  vector<vector<string>> kmap =
      vector<vector<string>>(numRows + 1, vector<string>(numCols + 1, "0"));

  vector<string> rowGrayCodes = generateGrayCode(variableTokens.size() / 2);
  vector<string> colGrayCodes =
      generateGrayCode(variableTokens.size() - variableTokens.size() / 2);

  for (int i = 0; i < numRows; i++) {
    string rowLabel;
    for (int j = 0; j < rowGrayCodes[i].size(); j++) {
      rowLabel += (rowGrayCodes[i][j] == '0')
                      ? variableTokens[j].value + string("'")
                      : string(1, variableTokens[j].value);
    }
    kmap[i + 1][0] = rowLabel;
  }

  // Fill in the column headers
  for (int i = 0; i < numCols; i++) {
    string colLabel;
    for (int j = 0; j < colGrayCodes[i].size(); j++) {
      colLabel +=
          (colGrayCodes[i][j] == '0')
              ? variableTokens[j + variableTokens.size() / 2].value +
                    string("'")
              : string(1, variableTokens[j + variableTokens.size() / 2].value);
    }
    kmap[0][i + 1] = colLabel;
  }

  kmap[0][0] = " ";

  for (int row = 0; row < numRows; row++) {
    for (int col = 0; col < numCols; col++) {
      int mintermValue = calculateMinterm(row, col, numCols);

      for (int piIndex = 0; piIndex < primeImplicants.size(); piIndex++) {
        const auto& implicant = primeImplicants[piIndex];

        // If the implicant covers the current minterm
        if (find(implicant.minterms.begin(), implicant.minterms.end(),
                 mintermValue) != implicant.minterms.end()) {
          if (kmap[row + 1][col + 1] == "0") {  // +1 to skip headers
            kmap[row + 1][col + 1] = "1 PI" + to_string(piIndex);
          } else {
            kmap[row + 1][col + 1] += " PI" + to_string(piIndex);
          }
        }
      }
    }
  }

  return kmap;
}