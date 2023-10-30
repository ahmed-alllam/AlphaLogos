#include "petrick.h"

#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "../logic_utils/minterm.h"
#include "essential_prime_implicants.h"
#include "implicant.h"

using namespace std;

void eliminateDominatingColumns(vector<Implicant> &PIs,
                                vector<Minterm> &uncovered_minterms) {
  for (int i = 0; i < uncovered_minterms.size(); i++) {
    for (int j = i + 1; j < uncovered_minterms.size(); j++) {
      bool isDominating = true;
      for (auto &implicant : PIs) {
        if (find(implicant.minterms.begin(), implicant.minterms.end(),
                 uncovered_minterms[j].index) != implicant.minterms.end() &&
            find(implicant.minterms.begin(), implicant.minterms.end(),
                 uncovered_minterms[i].index) == implicant.minterms.end()) {
          isDominating = false;
          break;
        }
      }
      if (isDominating) {
        uncovered_minterms.erase(uncovered_minterms.begin() + i);
        i--;
        break;
      }
    }
  }
}

void eliminateDominatedRows(vector<Implicant> &PIs,
                            vector<Minterm> &uncovered_minterms) {
  for (int i = 0; i < PIs.size(); i++) {
    for (int j = i + 1; j < PIs.size(); j++) {
      bool isDominated = true;
      for (int mintermIndex : PIs[i].minterms) {
        if (find(PIs[j].minterms.begin(), PIs[j].minterms.end(),
                 mintermIndex) == PIs[j].minterms.end()) {
          isDominated = false;
          break;
        }
      }
      if (isDominated) {
        PIs.erase(PIs.begin() + i);
        i--;
        break;
      }
    }
  }
}

vector<Implicant> doPetrickMinimization(vector<Implicant> PIs,
                                        vector<Implicant> EPIs,
                                        vector<Minterm> uncovered_minterms) {
  vector<Implicant> minimizedExpression;

  for (auto &EPI : EPIs) {
    minimizedExpression.push_back(EPI);
    for (int mt : EPI.minterms) {
      uncovered_minterms.erase(
          remove_if(uncovered_minterms.begin(), uncovered_minterms.end(),
                    [mt](Minterm m) { return m.index == mt; }),
          uncovered_minterms.end());
    }
  }

  while (!uncovered_minterms.empty()) {
    eliminateDominatingColumns(PIs, uncovered_minterms);
    eliminateDominatedRows(PIs, uncovered_minterms);

    int maxCoverIndex = 0;
    int maxCoverCount = 0;
    for (int i = 0; i < PIs.size(); i++) {
      int coverCount = 0;
      for (int mt : PIs[i].minterms) {
        if (find_if(uncovered_minterms.begin(), uncovered_minterms.end(),
                    [mt](Minterm m) { return m.index == mt; }) !=
            uncovered_minterms.end()) {
          coverCount++;
        }
      }
      if (coverCount > maxCoverCount) {
        maxCoverCount = coverCount;
        maxCoverIndex = i;
      }
    }

    minimizedExpression.push_back(PIs[maxCoverIndex]);

    for (int mintermIndex : PIs[maxCoverIndex].minterms) {
      for (int i = 0; i < uncovered_minterms.size(); i++) {
        if (uncovered_minterms[i].index == mintermIndex) {
          uncovered_minterms.erase(uncovered_minterms.begin() + i);
          break;
        }
      }
    }

    for (auto &PI : PIs) {
      for (int mt : PIs[maxCoverIndex].minterms) {
        PI.minterms.erase(remove(PI.minterms.begin(), PI.minterms.end(), mt),
                          PI.minterms.end());
      }
    }

    PIs.erase(PIs.begin() + maxCoverIndex);
  }

  return minimizedExpression;
}
