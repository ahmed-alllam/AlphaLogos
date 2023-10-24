#include "prime_implicants.h"

#include <algorithm>
#include <iostream>
#include <string>

#include "../logic_utils/minterm.h"
#include "../logic_utils/token.h"

using namespace std;

vector<Implicant> generatePrimeImplicants(vector<Minterm> minterms) {
  vector<Implicant> prime_implicants;
  vector<Implicant> column;

  for (const auto& minterm : minterms) {
    column.push_back({{minterm.index}, minterm.binary, false, false, false});
  }

  while (!column.empty()) {
    vector<Implicant> nextColumn;
    for (int i = 0; i < column.size(); i++) {
      for (int j = i + 1; j < column.size(); j++) {
        int num_diff = 0;
        int diff_index = -1;
        for (int k = 0; k < column[i].binary.size(); k++) {
          if (column[i].binary[k] != column[j].binary[k]) {
            num_diff++;
            diff_index = k;
          }
        }
        if (num_diff == 1) {
          vector<int> new_minterms(column[i].minterms);
          new_minterms.insert(new_minterms.end(), column[j].minterms.begin(),
                              column[j].minterms.end());
          vector<int> new_binary = column[i].binary;
          new_binary[diff_index] = -1;  // `-1` means `-`
          nextColumn.push_back({new_minterms, new_binary, false, false, false});
          column[i].is_checked = true;
          column[j].is_checked = true;
        }
      }
    }
    for (const auto& implicant : column) {
      if (!implicant.is_checked &&
          find(prime_implicants.begin(), prime_implicants.end(), implicant) ==
              prime_implicants.end()) {
        prime_implicants.push_back(implicant);
      }
    }
    column.swap(nextColumn);
  }

  return prime_implicants;
}
