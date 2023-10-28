#ifndef UNCOVERED_MINTERMS_H
#define UNCOVERED_MINTERMS_H
#include "../logic_utils/minterm.h"
#include "implicant.h"
vector<Minterm> getUncoveredMinterms(
    vector<Minterm>& minterms, const vector<Implicant>& essentialImplicants);

#endif