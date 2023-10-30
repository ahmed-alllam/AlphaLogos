#include "canonicals_handler.h"

#include <fstream>
#include <inja.hpp>
#include <iostream>
#include <string>
#include <vector>

#include "../logic_utils/canonical_forms.h"
#include "../logic_utils/maxterm.h"
#include "../logic_utils/minterm.h"
#include "../logic_utils/token.h"
#include "../logic_utils/truth_table_generator.h"

using namespace std;

void canonicals_handler(const crow::request &req, crow::response &res) {
  auto x = crow::json::load(req.body);

  if (!x) {
    res.code = 400;
    res.write("Invalid JSON");
    res.end();
    return;
  }

  string logic_expression = x["expression"].s();

  if (logic_expression == "") {
    res.code = 400;
    res.write("Empty expression");
    res.end();
    return;
  }

  vector<Token> tokens = tokenize(logic_expression);
  vector<Token> uniqueVariables = getUniqueVariables(tokens);
  vector<vector<bool>> truthTable = generateTruthTable(tokens);
  vector<Minterm> minTerms = generateMinTerms(uniqueVariables, truthTable);
  vector<Maxterm> maxTerms = generateMaxTerms(uniqueVariables, truthTable);

  string canonicalSoP = canonicalSoPToString(minTerms, uniqueVariables);
  string canonicalPoS = canonicalPoSToString(maxTerms, uniqueVariables);

  if (canonicalSoP == "") {
    canonicalSoP = "0";
  }

  if (canonicalPoS == "") {
    canonicalPoS = "1";
  }

  inja::Environment env;
  inja::Template canonicalsTemplate =
      env.parse_template("templates/canonicals.html");

  string result = env.render(
      canonicalsTemplate,
      {{"canonicalSoP", canonicalSoP}, {"canonicalPoS", canonicalPoS}});
  res.set_header("Content-Type", "text/html");
  res.write(result);
  res.end();

  return;
}