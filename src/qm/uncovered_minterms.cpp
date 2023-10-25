#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

#include "implicant.h"
#include "minterm.h"

vector<Minterm> getUncoveredMinterms(
    vector<Minterm>& minterms, const vector<Implicant>& essentialImplicants) {
  vector<Minterm> uncoveredMinterms;

  for (const Implicant& implicant : essentialImplicants) {
    for (int mintermIndex : implicant.minterms) {
      Minterm& minterm = minterms[mintermIndex];
      minterm.is_covered = true;
    }
  }

  for (Minterm& minterm : minterms) {
    if (!minterm.is_covered) {
      uncoveredMinterms.push_back(minterm);
    }
  }

  return uncoveredMinterms;
}
