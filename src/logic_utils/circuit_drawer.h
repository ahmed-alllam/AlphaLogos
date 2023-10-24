#ifndef CIRCUIT_DRAWER_H
#define CIRCUIT_DRAWER_H

#include <iostream>
#include <string>

#include "token.h"

using namespace std;

string SoPToWaveJSON(vector<Token> tokens);

string SoPToVerilog(vector<Token> tokens);

#endif  // CIRCUIT_DRAWER_H