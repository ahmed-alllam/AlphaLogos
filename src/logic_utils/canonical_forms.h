
#include <string>
#include <utility>
#include <vector>

#include "truth_table_generator.cpp"
#include "truth_table_generator.h"

using namespace std;
vector<Token> canonical_forms_sop(string expression);
vector<Token> canonical_forms_pos(string expression);
vector<Token> uniqueVariables(vector<Token> expression);