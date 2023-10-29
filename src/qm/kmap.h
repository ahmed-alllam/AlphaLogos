#ifndef KMAP_H
#define KMAP_H

#include <string>
#include <vector>

#include "../logic_utils/minterm.h"
#include "../logic_utils/token.h"
#include "implicant.h"

using namespace std;

string makeKMapLaTeX(vector<Implicant> primeImplicants,
                     vector<Token> variableTokens, vector<Minterm> minterms);

#endif  // KMAP_H