#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

#include "../logic_utils/minterm.h"
#include "implicant.h"

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

std::vector<std::pair<int, std::vector<std::vector<int>>>>
associatePrimeImplicants(const std::vector<Implicant>& implicants) {
  std::vector<std::pair<int, std::vector<std::vector<int>>>> result;

  // Create a map to store the prime implicants associated with each minterm
  std::unordered_map<int, std::vector<std::vector<int>>> mintermPrimeImplicants;

  // Collect all minterms from implicants and associate prime implicants
  for (const Implicant& implicant : implicants) {
    for (int minterm : implicant.minterms) {
      mintermPrimeImplicants[minterm].push_back(implicant.binary);
    }
  }

  // Create the result vector with minterm index and associated prime implicants
  for (const auto& entry : mintermPrimeImplicants) {
    int minterm = entry.first;
    const std::vector<std::vector<int>>& primeImplicants = entry.second;

    result.emplace_back(minterm, primeImplicants);
  }

  return result;
}

std::vector<int> findDominatingMinterms(
    const std::vector<std::pair<int, std::vector<std::vector<int>>>>&
        mintermPrimeImplicants) {
  std::unordered_set<int> dominatingMinterms;

  // Check for dominating minterms
  for (auto it1 = mintermPrimeImplicants.begin();
       it1 != mintermPrimeImplicants.end(); ++it1) {
    int minterm1 = it1->first;
    const std::vector<std::vector<int>>& primeImplicants1 = it1->second;

    for (auto it2 = std::next(it1); it2 != mintermPrimeImplicants.end();
         ++it2) {
      int minterm2 = it2->first;
      const std::vector<std::vector<int>>& primeImplicants2 = it2->second;

      bool isDominating = true;

      // Check if minterm1 dominates minterm2
      for (const std::vector<int>& implicant2 : primeImplicants2) {
        bool isCovered = false;

        for (const std::vector<int>& implicant1 : primeImplicants1) {
          if (std::equal(implicant2.begin(), implicant2.end(),
                         implicant1.begin())) {
            isCovered = true;
            break;
          }
        }

        if (!isCovered) {
          isDominating = false;
          break;
        }
      }

      if (isDominating) {
        dominatingMinterms.insert(minterm1);
        break;
      }
    }
  }

  return std::vector<int>(dominatingMinterms.begin(), dominatingMinterms.end());
}

vector<Implicant> removeDominatingMinterms(vector<Implicant>& implicants,
                                           const vector<int>& minterms) {
  vector<Implicant> filteredImplicants;

  for (const auto& implicant : implicants) {
    vector<int> remainingMinterms;
    for (const auto& m : implicant.minterms) {
      if (!binary_search(minterms.begin(), minterms.end(), m)) {
        remainingMinterms.push_back(m);
      }
    }
    filteredImplicants.push_back({remainingMinterms, implicant.binary,
                                  implicant.is_prime, implicant.is_essential,
                                  implicant.is_checked});
  }

  return filteredImplicants;
}

int main() {
  // Sample prime implicants
  std::vector<Implicant> implicants = {
      {{2, 3}, {0, 1, -1}, true, false, false},
      {{2, 3, 6, 7}, {-1, 1, -1}, true, false, false},
      {{3, 7}, {-1, 1, 1}, true, false, false}};

  // Print the original prime implicants
  std::cout << "Original prime implicants:" << std::endl;
  for (const auto& implicant : implicants) {
    std::cout << "Minterms: ";
    for (const auto& minterm : implicant.minterms) {
      std::cout << minterm << " ";
    }
    std::cout << std::endl;
  }

  cout << "-----------------------" << endl;

  std::vector<std::pair<int, std::vector<std::vector<int>>>> result =
      associatePrimeImplicants(implicants);

  // Display the associated prime implicants for each minterm
  for (const auto& entry : result) {
    int minterm = entry.first;
    const std::vector<std::vector<int>>& primeImplicants = entry.second;

    std::cout << "Minterm " << minterm << std::endl;
    std::cout << "Associated prime implicants: ";
    for (const std::vector<int>& implicant : primeImplicants) {
      std::cout << "(";
      for (int bit : implicant) {
        std::cout << bit << " ";
      }
      std::cout << ") ";
    }
    std::cout << std::endl << std::endl;
  }
  cout << "------------------------------" << endl;
  std::vector<int> dominatingMinterms = findDominatingMinterms(result);

  std::cout << "Dominating Minterms: ";
  for (int minterm : dominatingMinterms) {
    std::cout << minterm << " ";
  }
  std::cout << std::endl;

  vector<Implicant> filter_implicants =
      removeDominatingMinterms(implicants, dominatingMinterms);

  std::cout << "Remaining Implicants after removing dominating minterms:"
            << std::endl;
  for (const Implicant& implicant : filter_implicants) {
    std::cout << "Minterms: ";
    for (int minterm : implicant.minterms) {
      std::cout << minterm << " ";
    }
    std::cout << std::endl;
  }

  vector<Implicant> copy_implicants = implicants;
  int m = 5;
  while (m--) {
    copy_implicants = removeDominatedRows(copy_implicants);
    copy_implicants = removeDominatingMinterms(
        copy_implicants,
        findDominatingMinterms(associatePrimeImplicants(implicants)));
  }
  // Print the modified implicants
  for (const auto& implicant : copy_implicants) {
    cout << "Implicant: ";
    for (const auto& m : implicant.minterms) {
      cout << m << " ";
    }
    cout << endl;
    return 0;
  }
}