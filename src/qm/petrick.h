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

vector<Implicant> doPetrickMinimization(vector<Implicant> PIs,
                                        vector<Implicant> EPIs,
                                        vector<Minterm> uncovered_minterms);

#endif  // PETRICK_H