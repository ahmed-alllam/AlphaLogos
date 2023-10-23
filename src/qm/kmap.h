#ifndef KMAP_H
#define KMAP_H

#include <string>
#include <vector>

#include "../logic_utils/truth_table_generator.h"
#include "../qm/prime_implicants.h"

using namespace std;

vector<vector<string>> makeKMap(vector<Implicant> primeImplicants,
                                vector<Token> variableTokens,
                                vector<Minterm> minterms);

string makeKMapLaTeX(vector<Implicant> primeImplicants,
                     vector<Token> variableTokens, vector<Minterm> minterms);

#endif  // KMAP_H