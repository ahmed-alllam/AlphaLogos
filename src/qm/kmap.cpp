#include "kmap.h"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <set>
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

  for (const auto &str : previous) {
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

bool customSort(int a, int b, int num_vars) {
  std::vector<int> order = {0,  1,  3,  2,  4, 5, 7,  6,
                            12, 13, 15, 14, 8, 9, 11, 10};

  if (num_vars == 2) {
    order = {0, 1, 2, 3};
  }

  auto it_a = std::find(order.begin(), order.end(), a);
  auto it_b = std::find(order.begin(), order.end(), b);

  return it_a < it_b;
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
        const auto &implicant = primeImplicants[piIndex];

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

int mintermDistance(int a, int b, int num_vars) {
  std::vector<int> order = {0,  1,  3,  2,  4, 5, 7,  6,
                            12, 13, 15, 14, 8, 9, 11, 10};

  if (num_vars == 2) {
    order = {0, 1, 2, 3};
  } else if (num_vars == 3) {
    order = {0, 1, 3, 2, 4, 5, 7, 6};
  }

  auto getIndex = [&order](int value) -> int {
    return std::distance(order.begin(),
                         std::find(order.begin(), order.end(), value));
  };

  int columns = num_vars == 2 ? 2 : 4;

  // Same row case
  if (a / columns == b / columns) {
    int pos_a = getIndex(a);
    int pos_b = getIndex(b);
    return std::abs(pos_a - pos_b);
  }

  // Same column case
  if (getIndex(a) % columns == getIndex(b) % columns) {
    int pos_a = getIndex(a);
    int pos_b = getIndex(b);
    return std::abs(pos_a / columns - pos_b / columns);
  }

  // Diagonal case
  int pos_a = getIndex(a);
  int pos_b = getIndex(b);
  int row_dist = std::abs(pos_a / columns - pos_b / columns) + 1;
  int col_dist = std::abs(pos_a % columns - pos_b % columns) + 1;

  // Area of the rectangle connecting the two minterms
  return row_dist * col_dist - 1;
}

string generateLatexForImplicant(Implicant implicant, int num_vars) {
  vector<int> minterms = implicant.minterms;
  sort(minterms.begin(), minterms.end(),
       [num_vars](int a, int b) { return customSort(a, b, num_vars); });

  if (minterms.size() == 4 &&
      find(minterms.begin(), minterms.end(), 0) != minterms.end() &&
      find(minterms.begin(), minterms.end(), 2) != minterms.end() &&
      find(minterms.begin(), minterms.end(), 8) != minterms.end() &&
      find(minterms.begin(), minterms.end(), 10) != minterms.end()) {
    return "\\implicantcorner";
  }

  int distance =
      mintermDistance(minterms[0], minterms[minterms.size() - 1], num_vars);

  if (minterms.size() > distance) {
    return "\\implicant{" + to_string(minterms[0]) + "}{" +
           to_string(minterms[minterms.size() - 1]) + "}";
  }

  if (minterms.size() == 4 || minterms.size() == 8) {
    string s = "\\implicantedge";

    int minRow = 100;
    int minCol = 100;
    int maxRow = -1;
    int maxCol = -1;

    vector<int> order = {0, 1, 3, 2, 4, 5, 7, 6, 12, 13, 15, 14, 8, 9, 11, 10};

    if (num_vars == 2) {
      order = {0, 1, 2, 3};
    }

    auto getIndex = [&order](int value) -> int {
      return std::distance(order.begin(),
                           find(order.begin(), order.end(), value));
    };

    int num_cols = num_vars == 2 ? 2 : 4;

    for (int minterm : minterms) {
      int row = getIndex(minterm) / num_cols;
      int col = getIndex(minterm) % num_cols;

      if (row < minRow) {
        minRow = row;
      }
      if (row > maxRow) {
        maxRow = row;
      }
      if (col < minCol) {
        minCol = col;
      }
      if (col > maxCol) {
        maxCol = col;
      }
    }

    if (minterms[0] + 1 != minterms[1]) {
      s += "{" + to_string(order[minRow * num_cols + minCol]) + "}{" +
           to_string(order[maxRow * num_cols + minCol]) + "}{" +
           to_string(order[minRow * num_cols + maxCol]) + "}{" +
           to_string(order[maxRow * num_cols + maxCol]) + "}";
    } else {
      s += "{" + to_string(order[minRow * num_cols + minCol]) + "}{" +
           to_string(order[minRow * num_cols + maxCol]) + "}{" +
           to_string(order[maxRow * num_cols + minCol]) + "}{" +
           to_string(order[maxRow * num_cols + maxCol]) + "}";
    }

    return s;
  }

  if (minterms.size() == 2) {
    return "\\implicantedge{" + to_string(minterms[0]) + "}{" +
           to_string(minterms[0]) + "}" + "{" + to_string(minterms[1]) + "}{" +
           to_string(minterms[1]) + "}";
  }
}

string makeKMapLaTeX(vector<Implicant> primeImplicants,
                     vector<Token> variableTokens, vector<Minterm> minterms) {
  if (variableTokens.size() < 2 || variableTokens.size() > 4) {
    throw "Invalid number of variables for KMap.";
  }

  string latex = R"(


\documentclass[tikz, border=2mm]{standalone}
\usepackage{karnaugh-map}

  \begin{document}

  \begin {karnaugh-map})";

  if (variableTokens.size() == 2) {
    latex += "[2][2][1]";
  } else if (variableTokens.size() == 3) {
    latex += "[4][2][1]";
  } else {
    latex += "[4][4][1]";
  }

  for (int i = variableTokens.size() - 1; i >= 0; i--) {
    latex += "[$" + string(1, variableTokens[i].value) + "$]";
  }

  latex += "\n";

  int numRows = 1 << (variableTokens.size() / 2);
  int numCols = 1 << (variableTokens.size() - variableTokens.size() / 2);

  latex += "\\manualterms{";

  for (int row = 0; row < numRows; row++) {
    for (int col = 0; col < numCols; col++) {
      int mintermValue = row * numCols + col;

      bool found = false;
      for (Minterm minterm : minterms) {
        if (minterm.index == mintermValue) {
          latex += "1,";
          found = true;
          break;
        }
      }
      if (!found) {
        latex += "0,";
      }
    }
  }

  latex.pop_back();  // remove last comma
  latex += "}\n";

  for (Implicant implicant : primeImplicants) {
    latex += generateLatexForImplicant(implicant, variableTokens.size()) + "\n";
  }

  latex += "\\end{karnaugh-map}\n";

  latex += "\\end{document}\n";

  return latex;
}
