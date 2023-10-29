#ifndef PETRICK_H
#define PETRICK_H

// QuineMcCluskeySolver.h

#include <map>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "../logic_utils/minterm.h"
#include "implicant.h"

class QuineMcCluskeySolver {
 public:
  static std::vector<Implicant> removeImplicants(
      const std::vector<Implicant>& source,
      const std::vector<Implicant>& implicantsToRemove);

  static bool compareImplicants(const Implicant& a, const Implicant& b);

  static std::vector<Implicant> generateEssentialPrimeImplicants(
      const std::vector<Implicant>& primeImplicants);

  static std::vector<Implicant> removeDuplicateImplicants(
      const std::vector<Implicant>& implicants);

  static std::vector<Implicant> removeDominatedRows(
      const std::vector<Implicant>& implicants);

  static std::vector<Implicant> petrick(
      const std::vector<Implicant>& primeImplicant);

  // Assuming other functions like removeMinterms, getUniqueMinterms, etc. are
  // also public, add their declarations here.
};

#endif  // QUINE_MCCLUSKEY_SOLVER_H