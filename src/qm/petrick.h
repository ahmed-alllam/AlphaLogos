#ifndef PETRICK_H
#define PETRICK_H

#include <algorithm>
#include <iostream>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "../logic_utils/minterm.h"
#include "essential_prime_implicants.h"
#include "implicant.h"

using namespace std;

vector<Implicant> removeImplicants(const vector<Implicant>& source,
                                   const vector<Implicant>& implicantsToRemove);

vector<Implicant> removeDuplicateImplicants(
    const vector<Implicant>& implicants);

vector<Implicant> removeDominatedRows(const vector<Implicant>& implicants);

vector<pair<int, vector<vector<int>>>> associatePrimeImplicants(
    const vector<Implicant>& implicants);

vector<int> findDominatingMinterms(
    const vector<pair<int, vector<vector<int>>>>& mintermPrimeImplicants);

vector<Implicant> removeDominatingMinterms(vector<Implicant>& implicants,
                                           const vector<int>& minterms);

vector<int> getUniqueMinterms(vector<Implicant>& implicants);

vector<Implicant> removeMinterms(vector<Implicant>& implicants,
                                 const vector<int>& mintermsToRemove);

void printImplicant(vector<Implicant> v);

vector<Implicant> petrick(const vector<Implicant>& primeImplicant);

#endif  // PETRICK_H