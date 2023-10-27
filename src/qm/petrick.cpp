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

std::vector<Implicant> removeDominatingMinterms(
    const std::vector<Implicant>& primeImplicants) {
  std::vector<Implicant> result;

  for (const Implicant& implicant : primeImplicants) {
    Implicant modifiedImplicant = implicant;
    std::vector<int> nonDominatingMinterms;

    for (int minterm : modifiedImplicant.minterms) {
      bool isDominated = false;

      for (const Implicant& other : primeImplicants) {
        // Skip comparing with itself
        if (implicant == other) {
          continue;
        }

        // Check if minterm is dominated
        if (std::find(other.minterms.begin(), other.minterms.end(), minterm) !=
            other.minterms.end()) {
          isDominated = true;
          break;
        }
      }

      // Add the minterm to the non-dominating minterms if it is not dominated
      if (!isDominated) {
        nonDominatingMinterms.push_back(minterm);
      }
    }

    // Update the minterms of the modified implicant
    modifiedImplicant.minterms = nonDominatingMinterms;

    // Add the modified implicant to the result
    result.push_back(modifiedImplicant);
  }

  return result;
}

std::vector<Minterm> getUniqueMinterms(
    const std::vector<Implicant>& implicants) {
  std::unordered_set<int> uniqueMintermIndices;
  std::vector<Minterm> uniqueMinterms;

  // Iterate over each implicant and add its minterms to the set
  for (const Implicant& implicant : implicants) {
    for (int minterm : implicant.minterms) {
      uniqueMintermIndices.insert(minterm);
    }
  }

  // Create unique minterms from the set of indices
  for (int index : uniqueMintermIndices) {
    Minterm minterm;
    minterm.index = index;
    minterm.is_covered = false;
    // Assume binary and num_ones are already populated
    // based on your implementation

    uniqueMinterms.push_back(minterm);
  }

  return uniqueMinterms;
}

std::unordered_map<int, std::vector<Implicant>> getMintermsWithImplicants(
    const std::vector<Implicant>& implicants) {
  std::unordered_map<int, std::vector<Implicant>> mintermsWithImplicants;

  // Iterate over each implicant and add its minterms to the map
  for (const Implicant& implicant : implicants) {
    for (int minterm : implicant.minterms) {
      mintermsWithImplicants[minterm].push_back(implicant);
    }
  }

  return mintermsWithImplicants;
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

  // Remove subset implicants
  std::vector<Implicant> nonSubsetImplicants =
      removeDominatingMinterms(implicants);

  // Print the prime implicants after removal
  std::cout << "\nPrime implicants after removing subsets:" << std::endl;
  for (const auto& implicant : nonSubsetImplicants) {
    std::cout << "Minterms: ";
    for (const auto& minterm : implicant.minterms) {
      std::cout << minterm << " ";
    }
    std::cout << std::endl;
  }

  cout << "--------------------";

  std::unordered_map<int, std::vector<Implicant>> mintermsWithImplicants =
      getMintermsWithImplicants(implicants);

  // Print the minterms along with the implicants containing them
  for (const auto& entry : mintermsWithImplicants) {
    int minterm = entry.first;
    const std::vector<Implicant>& implicants = entry.second;

    std::cout << "Minterm: " << minterm << std::endl;
    std::cout << "Prime Implicants: ";
    for (const Implicant& implicant : implicants) {
      cout << "implicant minterms: ";
      for (int i = 0; i < implicant.minterms.size(); i++) {
        cout << implicant.minterms[i] << " ";
      }
      cout << endl;
    }
    std::cout << std::endl;
  }

  cout << "-----------------------";

  return 0;
}