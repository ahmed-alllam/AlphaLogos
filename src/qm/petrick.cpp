#include <algorithm>
#include <iostream>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

#include "../logic_utils/minterm.h"
#include "implicant.h"

vector<Implicant> removeImplicants(
    const vector<Implicant>& source,
    const vector<Implicant>& implicantsToRemove) {
  vector<Implicant> result = source;
  for (const auto& toRemove : implicantsToRemove) {
    result.erase(std::remove(result.begin(), result.end(), toRemove),
                 result.end());
  }
  return result;
}

bool compareImplicants(const Implicant& a, const Implicant& b) {
  if (a.minterms.size() != b.minterms.size()) {
    return a.minterms.size() < b.minterms.size();
  }
  return std::lexicographical_compare(a.minterms.begin(), a.minterms.end(),
                                      b.minterms.begin(), b.minterms.end());
}

vector<Implicant> generateEssentialPrimeImplicants(
    const vector<Implicant>& primeImplicants) {
  vector<Implicant> essentialImplicants;
  map<int, vector<const Implicant*>> mintermToImplicantMap;

  for (const auto& implicant : primeImplicants) {
    for (const int minterm : implicant.minterms) {
      mintermToImplicantMap[minterm].push_back(&implicant);
    }
  }

  for (const auto& pair : mintermToImplicantMap) {
    if (pair.second.size() == 1) {
      Implicant essentialImplicant = *(pair.second[0]);
      if (std::find(essentialImplicants.begin(), essentialImplicants.end(),
                    essentialImplicant) == essentialImplicants.end()) {
        essentialImplicants.push_back(essentialImplicant);
      }
    }
  }

  std::sort(essentialImplicants.begin(), essentialImplicants.end(),
            compareImplicants);
  return essentialImplicants;
}

vector<Implicant> removeDuplicateImplicants(
    const vector<Implicant>& implicants) {
  vector<Implicant> result;

  for (const Implicant& implicant : implicants) {
    if (std::find(result.begin(), result.end(), implicant) == result.end()) {
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
      if (i != j && std::includes(implicants[j].minterms.begin(),
                                  implicants[j].minterms.end(),
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

std::vector<int> getUniqueMinterms(std::vector<Implicant>& implicants) {
  std::unordered_set<int> uniqueMintermsSet;

  // Iterate over each implicant
  for (const auto& implicant : implicants) {
    // Add minterms to the set to ensure uniqueness
    for (int minterm : implicant.minterms) {
      uniqueMintermsSet.insert(minterm);
    }
  }

  // Convert the set to a vector
  std::vector<int> uniqueMinterms(uniqueMintermsSet.begin(),
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

void printImplicant(vector<Implicant> v) {
  cout << "The vector of implicant are: " << endl;
  for (int i = 0; i < v.size(); i++) {
    for (int j = 0; j < v[i].binary.size(); j++) {
      cout << v[i].binary[j] << " ";
    }
    cout << endl;
  }
}

vector<Implicant> petrick(const vector<Implicant>& primeImplicant) {
  vector<Implicant> copy_implicants = primeImplicant;
  vector<Implicant> solution;

  while (!copy_implicants.empty()) {
    vector<Implicant> temp_epi =
        generateEssentialPrimeImplicants(copy_implicants);
    solution.insert(solution.end(), temp_epi.begin(), temp_epi.end());

    copy_implicants = removeImplicants(copy_implicants, temp_epi);
    copy_implicants =
        removeMinterms(copy_implicants, getUniqueMinterms(temp_epi));
    copy_implicants = removeDuplicateImplicants(copy_implicants);
    copy_implicants = removeDominatedRows(copy_implicants);
    copy_implicants = removeDominatingMinterms(
        copy_implicants,
        findDominatingMinterms(associatePrimeImplicants(copy_implicants)));
  }

  return removeDuplicateImplicants(solution);
}

int main() {
  // Sample prime implicants
  std::vector<Implicant> implicants = {
      {{0, 2, 4, 6}, {0, -1, -1, 0}, false, false, false},
      {{0, 1, 8, 9}, {-1, 0, 0, -1}, false, false, false},
      {{9, 11, 13, 15}, {1, -1, -1, 1}, false, false, false},
  };

  // Print the original prime implicants
  std::cout << "Original prime implicants:" << std::endl;
  for (const auto& implicant : implicants) {
    std::cout << "Minterms: ";
    for (const auto& minterm : implicant.minterms) {
      std::cout << minterm << " ";
    }
    std::cout << std::endl;
  }

  vector<Implicant> copy_implicants = petrick(implicants);
  // Print the modified implicants
  cout << "Finalised answer: " << endl;
  for (const auto& implicant : copy_implicants) {
    cout << "Implicant: ";
    for (const auto& m : implicant.binary) {
      cout << m << " ";
    }
    cout << endl;
  }
}