#include "essential_prime_implicants.h"

#include <map>
using namespace std;

bool compareImplicants(const Implicant& a, const Implicant& b) {
  if (a.minterms.size() != b.minterms.size()) {
    return a.minterms.size() < b.minterms.size();
  }

  // Both have the same size
  for (size_t i = 0; i < a.minterms.size(); ++i) {
    if (a.minterms[i] != b.minterms[i]) {
      return a.minterms[i] < b.minterms[i];
    }
  }

  // If they're equivalent at this point, return false (since neither is "less"
  // than the other)
  return false;
}
vector<Implicant> generateEssentialPrimeImplicants(
    const vector<Implicant>& primeImplicants) {
  vector<Implicant> essentialImplicants;
  map<int, vector<const Implicant*>> mintermToImplicantMap;

  // Map minterms to the implicants they belong to
  for (const auto& implicant : primeImplicants) {
    for (const int minterm : implicant.minterms) {
      mintermToImplicantMap[minterm].push_back(&implicant);
    }
  }

  for (const auto& pair : mintermToImplicantMap) {
    // If a minterm is covered by only one prime implicant, that implicant is
    // essential
    if (pair.second.size() == 1) {
      Implicant essentialImplicant = *(pair.second[0]);
      if (find(essentialImplicants.begin(), essentialImplicants.end(),
               essentialImplicant) == essentialImplicants.end()) {
        essentialImplicants.push_back(essentialImplicant);
      }
    }
  }

  // Sort the essentialImplicants vector
  sort(essentialImplicants.begin(), essentialImplicants.end(),
       compareImplicants);

  return essentialImplicants;
}
