#ifndef UNCOVERED_MINTERMS_H
#define UNCOVERED_MINTERMS_H
#include "implicant.h"
#include "minterm.h"
vector<int> getUncoveredMinterms(vector<Minterm>& minterms,
                                 const vector<Implicant>& essentialImplicants);

#endif