#include <algorithm>
#include <iostream>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

#include "../logic_utils/minterm.h"
#include "essential_prime_implicants.h"
#include "implicant.h"
#include "petrick.h"

vector<Implicant> removeImplicants(
    const vector<Implicant>& source,
    const vector<Implicant>& implicantsToRemove) {
  vector<Implicant> result = source;
  for (const auto& toRemove : implicantsToRemove) {
    result.erase(remove(result.begin(), result.end(), toRemove), result.end());
  }
  return result;
}

vector<Implicant> removeDuplicateImplicants(
    const vector<Implicant>& implicants) {
  vector<Implicant> result;

  for (const Implicant& implicant : implicants) {
    if (find(result.begin(), result.end(), implicant) == result.end()) {
      result.push_back(implicant);
    }
  }

  return result;
}

vector<Implicant> removeDominatedRows(const vector<Implicant>& implicants) {
  vector<Implicant> result;

  for (size_t i = 0; i < implicants.size(); ++i) {
    bool isDominated = false;
    for (size_t j = 0; j < implicants.size(); ++j) {
      if (i != j &&
          includes(implicants[j].minterms.begin(), implicants[j].minterms.end(),
                   implicants[i].minterms.begin(),
                   implicants[i].minterms.end())) {
        isDominated = true;
        break;
      }
    }
    if (!isDominated) {
      result.push_back(implicants[i]);
    }
  }

  return result;
}

vector<pair<int, vector<vector<int>>>> associatePrimeImplicants(
    const vector<Implicant>& implicants) {
  vector<pair<int, vector<vector<int>>>> result;

  // Create a map to store the prime implicants associated with each minterm
  unordered_map<int, vector<vector<int>>> mintermPrimeImplicants;

  // Collect all minterms from implicants and associate prime implicants
  for (const Implicant& implicant : implicants) {
    for (int minterm : implicant.minterms) {
      mintermPrimeImplicants[minterm].push_back(implicant.binary);
    }
  }

  // Create the result vector with minterm index and associated prime implicants
  for (const auto& entry : mintermPrimeImplicants) {
    int minterm = entry.first;
    const vector<vector<int>>& primeImplicants = entry.second;

    result.emplace_back(minterm, primeImplicants);
  }

  return result;
}

vector<int> findDominatingMinterms(
    const vector<pair<int, vector<vector<int>>>>& mintermPrimeImplicants) {
  unordered_set<int> dominatingMinterms;

  // Check for dominating minterms
  for (auto it1 = mintermPrimeImplicants.begin();
       it1 != mintermPrimeImplicants.end(); ++it1) {
    int minterm1 = it1->first;
    const vector<vector<int>>& primeImplicants1 = it1->second;

    for (auto it2 = next(it1); it2 != mintermPrimeImplicants.end(); ++it2) {
      int minterm2 = it2->first;
      const vector<vector<int>>& primeImplicants2 = it2->second;

      bool isDominating = true;

      // Check if minterm1 dominates minterm2
      for (const vector<int>& implicant2 : primeImplicants2) {
        bool isCovered = false;

        for (const vector<int>& implicant1 : primeImplicants1) {
          if (equal(implicant2.begin(), implicant2.end(), implicant1.begin())) {
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

  return vector<int>(dominatingMinterms.begin(), dominatingMinterms.end());
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

vector<int> getUniqueMinterms(vector<Implicant>& implicants) {
  unordered_set<int> uniqueMintermsSet;

  // Iterate over each implicant
  for (const auto& implicant : implicants) {
    // Add minterms to the set to ensure uniqueness
    for (int minterm : implicant.minterms) {
      uniqueMintermsSet.insert(minterm);
    }
  }

  // Convert the set to a vector
  vector<int> uniqueMinterms(uniqueMintermsSet.begin(),
                             uniqueMintermsSet.end());

  return uniqueMinterms;
}

vector<Implicant> removeMinterms(vector<Implicant>& implicants,
                                 const vector<int>& mintermsToRemove) {
  for (auto& implicant : implicants) {
    // Create a copy of the implicant's minterms
    vector<int> updatedMinterms = implicant.minterms;

    // Iterate over the minterms to remove
    for (const auto& mintermToRemove : mintermsToRemove) {
      // Find and remove the minterm from the updated minterms
      auto it =
          find(updatedMinterms.begin(), updatedMinterms.end(), mintermToRemove);
      if (it != updatedMinterms.end()) {
        updatedMinterms.erase(it);
      }
    }

    // Update the implicant's minterms
    implicant.minterms = updatedMinterms;
  }

  return implicants;
}

Implicant findMaxMintermImplicant(const vector<Implicant>& implicants) {
  Implicant maxMintermImplicant;
  size_t maxMinterms = 0;

  for (const auto& implicant : implicants) {
    if (implicant.minterms.size() > maxMinterms) {
      maxMinterms = implicant.minterms.size();
      maxMintermImplicant = implicant;
    }
  }

  return maxMintermImplicant;
}

vector<Implicant> petrick(const vector<Implicant>& primeImplicant) {
  vector<pair<Implicant, vector<int>>> primeImplicantMinterms;
  vector<Implicant> copy_implicants = primeImplicant;
  vector<Implicant> solution;
  int size = 0;
  while (copy_implicants.size() > 0) {
    primeImplicantMinterms
        .clear();  // Clear the vector before populating it again

    for (const auto& implicant : primeImplicant) {
      primeImplicantMinterms.emplace_back(implicant, implicant.minterms);
    }

    vector<Implicant> temp_epi =
        generateEssentialPrimeImplicants(copy_implicants);
    solution.insert(solution.end(), temp_epi.begin(), temp_epi.end());
    if (size == solution.size()) {
      temp_epi = vector<Implicant>{findMaxMintermImplicant(copy_implicants)};
      solution.insert(solution.end(), temp_epi.begin(), temp_epi.end());
      copy_implicants = removeImplicants(copy_implicants, temp_epi);
      copy_implicants =
          removeMinterms(copy_implicants, getUniqueMinterms(temp_epi));
    } else {
      size = solution.size();
    }
    copy_implicants = removeImplicants(copy_implicants, temp_epi);
    copy_implicants =
        removeMinterms(copy_implicants, getUniqueMinterms(temp_epi));
    copy_implicants = removeDominatedRows(copy_implicants);
    copy_implicants = removeDominatingMinterms(
        copy_implicants,
        findDominatingMinterms(associatePrimeImplicants(copy_implicants)));
  }

  solution = removeDuplicateImplicants(solution);

  for (auto& implicant : solution) {
    for (auto& original_implicant : primeImplicantMinterms) {
      if (implicant.binary == original_implicant.first.binary) {
        implicant.minterms = original_implicant.second;
      }
    }
  }

  return solution;
}