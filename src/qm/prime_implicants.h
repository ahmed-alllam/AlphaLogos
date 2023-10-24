#ifndef PRIME_IMPLICANTS_H
#define PRIME_IMPLICANTS_H

#include <algorithm>
#include <string>
#include <vector>

#include "../logic_utils/minterm.h"
#include "../logic_utils/token.h"
#include "implicant.h"

using namespace std;

vector<Implicant> generatePrimeImplicants(vector<Minterm> minterms);

#endif  // PRIME_IMPLICANTS_H
