#include "kmap.h"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <set>
#include <string>
#include <vector>

#include "../logic_utils/minterm.h"
#include "../logic_utils/token.h"
#include "implicant.h"

using namespace std;

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

int mintermDistance(int a, int b, int num_vars) {
  std::vector<int> order = {0,  1,  3,  2,  4, 5, 7,  6,
                            12, 13, 15, 14, 8, 9, 11, 10};

  if (num_vars == 2) {
    order = {0, 1, 2, 3};
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

    if (abs(minterms[0] - minterms[1]) != 1) {
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

  return "";
}

string makeKMapLaTeX(vector<Implicant> primeImplicants,
                     vector<Token> variableTokens, vector<Minterm> minterms) {
  if (variableTokens.size() < 2 || variableTokens.size() > 4) {
    throw "Invalid number of variables for KMap.";
  }

  string latex = R"(


  \documentclass{standalone}
  \usepackage{karnaugh-map}

  \begin{document}

  \hspace{1pt}

  \begin {karnaugh-map})";

  if (variableTokens.size() == 2) {
    latex += "[2][2][1]";
  } else if (variableTokens.size() == 3) {
    latex += "[4][2][1]";
  } else {
    latex += "[4][4][1]";
  }

  for (int i = 0; i < variableTokens.size(); i++) {
    latex += "[$" + string(1, variableTokens[i].value) + "$]";
  }

  latex += "\n";

  int numRows = 1 << (variableTokens.size() / 2);
  int numCols = 1 << (variableTokens.size() - variableTokens.size() / 2);

  latex += "\\minterms{";

  for (Minterm minterm : minterms) {
    latex += to_string(minterm.index) + ",";
  }

  latex.pop_back();  // remove last comma
  latex += "}\n";

  latex += "\\autoterms[0]\n";

  // ToDo: put first the EPIs, and avoid redundancy of the PIs

  for (Implicant implicant : primeImplicants) {
    latex += generateLatexForImplicant(implicant, variableTokens.size()) + "\n";
  }

  latex += "\\end{karnaugh-map}\n";

  latex += "\\end{document}\n";

  return latex;
}
