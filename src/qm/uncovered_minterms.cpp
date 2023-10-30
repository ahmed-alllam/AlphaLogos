#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

#include "../logic_utils/minterm.h"
#include "implicant.h"

vector<Minterm> getUncoveredMinterms(
    vector<Minterm>& minterms, const vector<Implicant>& essentialImplicants) {
  vector<Minterm> uncoveredMinterms;

  for (Minterm& minterm : minterms) {
    minterm.is_covered = false;
  }

  for (const Implicant& implicant : essentialImplicants) {
    for (int mintermIndex : implicant.minterms) {
      for (Minterm& minterm : minterms) {
        if (minterm.index == mintermIndex) {
          minterm.is_covered = true;
          break;
        }
      }
    }
  }

  for (Minterm& minterm : minterms) {
    if (!minterm.is_covered) {
      uncoveredMinterms.push_back(minterm);
    }
  }

  return uncoveredMinterms;
}
