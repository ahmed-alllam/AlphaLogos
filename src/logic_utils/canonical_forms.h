#include <string>
#include <utility>
#include <vector>

#include "maxterm.h"
#include "minterm.h"
#include "token.h"

using namespace std;

vector<Minterm> generateMinTerms(vector<Token> uniqueVariables,
                                 vector<vector<bool>> truthTable);

vector<Maxterm> generateMaxTerms(vector<Token> uniqueVariables,
                                 vector<vector<bool>> truthTable);
