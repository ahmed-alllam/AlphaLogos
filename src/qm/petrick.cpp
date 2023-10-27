#include <algorithm>
#include <iostream>
#include <vector>

#include "implicant.h"
using namespace std;

vector<Implicant> removeDominatedRows(
    const std::vector<Implicant>& implicants) {
  std::vector<Implicant> result;
  std::vector<bool> isDominated(implicants.size(), false);

  for (int i = 0; i < implicants.size(); i++) {
    if (isDominated[i]) {
      continue;  // Skip implicants marked as dominated
    }

    for (int j = 0; j < implicants.size(); j++) {
      if (i != j && std::includes(implicants[j].minterms.begin(),
                                  implicants[j].minterms.end(),
                                  implicants[i].minterms.begin(),
                                  implicants[i].minterms.end())) {
        isDominated[i] = true;
        break;
      }
    }

    if (!isDominated[i]) {
      result.push_back(implicants[i]);
    }
  }

  return result;
}