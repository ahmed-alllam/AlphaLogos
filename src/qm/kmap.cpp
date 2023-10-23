#include "kmap.h"

#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <vector>

#include "../logic_utils/truth_table_generator.h"
#include "../qm/prime_implicants.h"

using namespace std;

void replaceVariable(string &str, const string &placeholder,
                     const string &replacement) {
  int pos;
  while ((pos = str.find(placeholder)) != string::npos) {
    str.replace(pos, placeholder.length(), replacement);
  }
}

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

string randomColor() {
  // random color from list of LaTeX colors, choose only strong colors that
  // would be visible on a white background and are not too similar to each
  // other
  vector<string> colors = {"red",     "blue",   "green",  "cyan",
                           "magenta", "yellow", "orange", "teal",
                           "olive",   "lime",   "brown",  "black"};
  return colors[rand() % colors.size()];
}

int binaryToGray(int num) { return num ^ (num >> 1); }

int calculateMinterm(int row, int col, int numCols) {
  int grayRow = binaryToGray(row);
  int grayCol = binaryToGray(col);
  return grayRow * numCols + grayCol;
}

bool customSort(int a, int b) {
  std::vector<int> order = {0,  1,  3,  2,  4, 5, 7,  6,
                            12, 13, 15, 14, 8, 9, 11, 10};

  // Find the index of 'a' and 'b' in the order vector
  auto it_a = std::find(order.begin(), order.end(), a);
  auto it_b = std::find(order.begin(), order.end(), b);

  // Compare the positions in the order vector
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

string generateLatexForImplicant(Implicant implicant, int num_vars,
                                 string color) {
  vector<int> minterms = implicant.minterms;
  sort(minterms.begin(), minterms.end(), customSort);

  if (minterms.size() == 1) {
    return "\\implicantsol{" + to_string(minterms[0]) + "}{" + color + "}";
  }

  std::vector<int> diffs;
  for (int i = 0; i < minterms.size() - 1; ++i) {
    diffs.push_back(minterms[i + 1] - minterms[i]);
  }

  // 2-variable K-map
  if (num_vars == 2) {
    if (std::find(diffs.begin(), diffs.end(), 2) != diffs.end()) {
      return "\\implicantdaltbaix{" + std::to_string(minterms[0]) + "}{" +
             std::to_string(minterms.back()) + "}{" + color + "}";
    }
    return "\\implicant{" + std::to_string(minterms[0]) + "}{" +
           std::to_string(minterms.back()) + "}{" + color + "}";
  }

  // 3-variable K-map
  if (num_vars == 3) {
    if (std::find(diffs.begin(), diffs.end(), 2) != diffs.end()) {
      return "\\implicantcostats{" + std::to_string(minterms[0]) + "}{" +
             std::to_string(minterms.back()) + "}{" + color + "}";
    }
    if (std::find(diffs.begin(), diffs.end(), 4) != diffs.end()) {
      return "\\implicantdaltbaix{" + std::to_string(minterms[0]) + "}{" +
             std::to_string(minterms.back()) + "}{" + color + "}";
    }
    return "\\implicant{" + std::to_string(minterms[0]) + "}{" +
           std::to_string(minterms.back()) + "}{" + color + "}";
  }

  // 4-variable K-map
  if (num_vars == 4) {
    if (std::find(diffs.begin(), diffs.end(), 1) != diffs.end()) {
      return "\\implicant{" + std::to_string(minterms[0]) + "}{" +
             std::to_string(minterms.back()) + "}{" + color + "}";
    }
    if (std::find(diffs.begin(), diffs.end(), 4) != diffs.end()) {
      return "\\implicantdaltbaix{" + std::to_string(minterms[0]) + "}{" +
             std::to_string(minterms.back()) + "}{" + color + "}";
    }
    if (minterms == std::vector<int>{0, 2, 8, 10}) {
      return "\\implicantcantons{" + color + "}";
    }
    return "\\implicant{" + std::to_string(minterms[0]) + "}{" +
           std::to_string(minterms.back()) + "}{" + color + "}";
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


  \makeatletter
  \def\normalsize{\@setfontsize\normalsize{12pt}{14.5pt}}
  \makeatother


  \usepackage{tikz}
  \usetikzlibrary{matrix,calc}

  \newcommand{\implicantsol}[3][0]{
    \draw[rounded corners=3pt, fill=#3, opacity=0.3] ($(#2.north west)+(135:#1)$) rectangle ($(#2.south east)+(-45:#1)$);
    }

  \newcommand{\implicant}[4][0]{
    \draw[rounded corners=3pt, fill=#4, opacity=0.3] ($(#2.north west)+(135:#1)$) rectangle ($(#3.south east)+(-45:#1)$);
    }

  \newcommand{\implicantcostats}[4][0]{
    \draw[rounded corners=3pt, fill=#4, opacity=0.3] ($(rf.east |- #2.north)+(90:#1)$)-| ($(#2.east)+(0:#1)$) |- ($(rf.east |- #3.south)+(-90:#1)$);
    \draw[rounded corners=3pt, fill=#4, opacity=0.3] ($(cf.west |- #2.north)+(90:#1)$) -| ($(#3.west)+(180:#1)$) |- ($(cf.west |- #3.south)+(-90:#1)$);
  }

  \newcommand{\implicantdaltbaix}[4][0]{
    \draw[rounded corners=3pt, fill=#4, opacity=0.3] ($(cf.south -| #2.west)+(180:#1)$) |- ($(#2.south)+(-90:#1)$) -| ($(cf.south -| #3.east)+(0:#1)$);
    \draw[rounded corners=3pt, fill=#4, opacity=0.3] ($(rf.north -| #2.west)+(180:#1)$) |- ($(#3.north)+(90:#1)$) -| ($(rf.north -| #3.east)+(0:#1)$);
  }

  \newcommand{\implicantcantons}[2][0]{
    \draw[rounded corners=3pt, opacity=.3] ($(rf.east |- 0.south)+(-90:#1)$) -| ($(0.east |- cf.south)+(0:#1)$);
    \draw[rounded corners=3pt, opacity=.3] ($(rf.east |- 8.north)+(90:#1)$) -| ($(8.east |- rf.north)+(0:#1)$);
    \draw[rounded corners=3pt, opacity=.3] ($(cf.west |- 2.south)+(-90:#1)$) -| ($(2.west |- cf.south)+(180:#1)$);
    \draw[rounded corners=3pt, opacity=.3] ($(cf.west |- 10.north)+(90:#1)$) -| ($(10.west |- rf.north)+(180:#1)$);
    \fill[rounded corners=3pt, fill=#2, opacity=.3] ($(rf.east |- 0.south)+(-90:#1)$) -|  ($(0.east |- cf.south)+(0:#1)$) [sharp corners] ($(rf.east |- 0.south)+(-90:#1)$) |-  ($(0.east |- cf.south)+(0:#1)$) ;
    \fill[rounded corners=3pt, fill=#2, opacity=.3] ($(rf.east |- 8.north)+(90:#1)$) -| ($(8.east |- rf.north)+(0:#1)$) [sharp corners] ($(rf.east |- 8.north)+(90:#1)$) |- ($(8.east |- rf.north)+(0:#1)$) ;
    \fill[rounded corners=3pt, fill=#2, opacity=.3] ($(cf.west |- 2.south)+(-90:#1)$) -| ($(2.west |- cf.south)+(180:#1)$) [sharp corners]($(cf.west |- 2.south)+(-90:#1)$) |- ($(2.west |- cf.south)+(180:#1)$) ;
    \fill[rounded corners=3pt, fill=#2, opacity=.3] ($(cf.west |- 10.north)+(90:#1)$) -| ($(10.west |- rf.north)+(180:#1)$) [sharp corners] ($(cf.west |- 10.north)+(90:#1)$) |- ($(10.west |- rf.north)+(180:#1)$) ;
  }

  \newenvironment{Karnaugh}%
  {
  \begin{tikzpicture}[baseline=(current bounding box.north),scale=0.8]
  \draw (0,0) grid (4,4);
  \draw (0,4) -- node [pos=0.7,above right,anchor=south west] {{var3}{var4}} node [pos=0.7,below left,anchor=north east] {{var1}{var2}} ++(135:1);

  \matrix (mapa) [matrix of nodes,
        column sep={0.8cm,between origins},
        row sep={0.8cm,between origins},
        every node/.style={minimum size=0.3mm},
        anchor=8.center,
        ampersand replacement=\&] at (0.5,0.5)
  {
                        \& |(c00)| 00         \& |(c01)| 01         \& |(c11)| 11         \& |(c10)| 10         \& |(cf)| \phantom{00} \\
  |(r00)| 00             \& |(0)|  \phantom{0} \& |(1)|  \phantom{0} \& |(3)|  \phantom{0} \& |(2)|  \phantom{0} \&                     \\
  |(r01)| 01             \& |(4)|  \phantom{0} \& |(5)|  \phantom{0} \& |(7)|  \phantom{0} \& |(6)|  \phantom{0} \&                     \\
  |(r11)| 11             \& |(12)| \phantom{0} \& |(13)| \phantom{0} \& |(15)| \phantom{0} \& |(14)| \phantom{0} \&                     \\
  |(r10)| 10             \& |(8)|  \phantom{0} \& |(9)|  \phantom{0} \& |(11)| \phantom{0} \& |(10)| \phantom{0} \&                     \\
  |(rf) | \phantom{00}   \&                    \&                    \&                    \&                    \&                     \\
  };
  }%
  {
  \end{tikzpicture}
  }

  %Empty Karnaugh map 2x4
  \newenvironment{Karnaughvuit}%
  {
  \begin{tikzpicture}[baseline=(current bounding box.north),scale=0.8]
  \draw (0,0) grid (4,2);
  \draw (0,2) -- node [pos=0.7,above right,anchor=south west] {{var2}{var3}} node [pos=0.7,below left,anchor=north east] {{var1}} ++(135:1);
  %
  \matrix (mapa) [matrix of nodes,
        column sep={0.8cm,between origins},
        row sep={0.8cm,between origins},
        every node/.style={minimum size=0.3mm},
        anchor=4.center,
        ampersand replacement=\&] at (0.5,0.5)
  {
                      \& |(c00)| 00         \& |(c01)| 01         \& |(c11)| 11         \& |(c10)| 10         \& |(cf)| \phantom{00} \\
  |(r00)| 0             \& |(0)|  \phantom{0} \& |(1)|  \phantom{0} \& |(3)|  \phantom{0} \& |(2)|  \phantom{0} \&                     \\
  |(r01)| 1             \& |(4)|  \phantom{0} \& |(5)|  \phantom{0} \& |(7)|  \phantom{0} \& |(6)|  \phantom{0} \&                     \\
  |(rf) | \phantom{00}  \&                    \&                    \&                    \&                    \&                     \\
  };
  }%
  {
  \end{tikzpicture}
  }

  \newenvironment{Karnaughquatre}%
  {
  \begin{tikzpicture}[baseline=(current bounding box.north),scale=0.8]
  \draw (0,0) grid (2,2);
  \draw (0,2) -- node [pos=0.7,above right,anchor=south west] {{var2}} node [pos=0.7,below left,anchor=north east] {{var1}} ++(135:1);
  %
  \matrix (mapa) [matrix of nodes,
        column sep={0.8cm,between origins},
        row sep={0.8cm,between origins},
        every node/.style={minimum size=0.3mm},
        anchor=2.center,
        ampersand replacement=\&] at (0.5,0.5)
  {
          \& |(c00)| 0          \& |(c01)| 1  \\
  |(r00)| 0 \& |(0)|  \phantom{0} \& |(1)|  \phantom{0} \\
  |(r01)| 1 \& |(2)|  \phantom{0} \& |(3)|  \phantom{0} \\
  };
  }%
  {
  \end{tikzpicture}
  }

  \newcommand{\contingut}[1]{%
  \foreach \x [count=\xi from 0]  in {#1}
      \path (\xi) node {\x};
  }

  \newcommand{\minterms}[1]{%
    \foreach \x in {#1}
        \path (\x) node {1};
  }

  \newcommand{\maxterms}[1]{%
    \foreach \x in {#1}
        \path (\x) node {0};
  }

  \begin{document}


  )";

  if (variableTokens.size() == 2) {
    latex += "\\begin{Karnaughquatre}\n";
  } else if (variableTokens.size() == 3) {
    latex += "\\begin{Karnaughvuit}\n";
  } else {
    latex += "\\begin{Karnaugh}\n";
  }

  int numRows = 1 << (variableTokens.size() / 2);
  int numCols = 1 << (variableTokens.size() - variableTokens.size() / 2);

  latex += "\\contingut{";

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

  for (int i = 0; i < variableTokens.size(); ++i) {
    string placeholder = "{var" + to_string(i + 1) + "}";
    int pos;
    while ((pos = latex.find(placeholder)) != string::npos) {
      replaceVariable(latex, placeholder, string(1, variableTokens[i].value));
    }
  }

  for (Implicant implicant : primeImplicants) {
    latex += generateLatexForImplicant(implicant, variableTokens.size(),
                                       randomColor()) +
             "\n";
  }

  if (variableTokens.size() == 2) {
    latex += "\\end{Karnaughquatre}\n";
  } else if (variableTokens.size() == 3) {
    latex += "\\end{Karnaughvuit}\n";
  } else {
    latex += "\\end{Karnaugh}\n";
  }

  latex += "\\end{document}\n";

  return latex;
}
