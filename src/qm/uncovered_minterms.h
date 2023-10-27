#ifndef UNCOVERED_MINTERMS_H
#define UNCOVERED_MINTERMS_H
#include "../src/logic_utils/minterm.h"
#include "implicant.h"
vector<int> getUncoveredMinterms(vector<Minterm>& minterms,
                                 const vector<Implicant>& essentialImplicants);

#endif