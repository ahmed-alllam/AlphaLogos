#ifndef PETRICK_H
#define PETRICK_H

#include <algorithm>
#include <vector>

#include "implicant.h"

using namespace std;

vector<Implicant> removeDominatedRows(const std::vector<Implicant>& implicants);

#endif  // IMPLICANT_UTILS_H