#ifndef ESSENTIAL_PRIME_IMPLICANTS_H
#define ESSENTIAL_PRIME_IMPLICANTS_H

#include <vector>

#include "implicant.h"

using namespace std;

vector<Implicant> generateEssentialPrimeImplicants(
    const std::vector<Implicant>& primeImplicants);
bool compareImplicants(const Implicant& a, const Implicant& b);
#endif  // ESSENTIAL_IMPLICANTS_H
