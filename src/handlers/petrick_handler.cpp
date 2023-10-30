#include "petrick_handler.h"

#include <fstream>
#include <inja.hpp>
#include <iostream>
#include <string>
#include <vector>

#include "../logic_utils/canonical_forms.h"
#include "../logic_utils/minterm.h"
#include "../logic_utils/token.h"
#include "../logic_utils/truth_table_generator.h"
#include "../qm/implicant.h"
#include "../qm/petrick.h"
#include "../qm/prime_implicants.h"

using namespace std;

void petrick_handler(const crow::request &req, crow::response &res) {
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

  // ToDo: Added if to check if minterms do not exceed a big number

  vector<Implicant> primeImplicants = generatePrimeImplicants(minTerms);

  vector<Implicant> minimizedImplicants = petrick(primeImplicants);

  string minimizedImplicantsString = "";
  for (auto &implicant : minimizedImplicants) {
    minimizedImplicantsString += implicantToString(implicant, uniqueVariables);

    if (&implicant != &minimizedImplicants.back()) {
      minimizedImplicantsString += " + ";
    }
  }

  inja::Environment env;
  inja::Template petrickTemplate = env.parse_template("templates/petrick.html");

  string result =
      env.render(petrickTemplate,
                 {{"minimizedImplicantsString", minimizedImplicantsString}});

  res.set_header("Content-Type", "text/html");
  res.write(result);
  res.end();

  return;
}