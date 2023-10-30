#include "epi_handler.h"

#include <fstream>
#include <inja.hpp>
#include <iostream>
#include <string>
#include <vector>

#include "../logic_utils/canonical_forms.h"
#include "../logic_utils/minterm.h"
#include "../logic_utils/token.h"
#include "../logic_utils/truth_table_generator.h"
#include "../qm/essential_prime_implicants.h"
#include "../qm/implicant.h"
#include "../qm/prime_implicants.h"

using namespace std;

void epi_handler(const crow::request &req, crow::response &res) {
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

  if (minTerms.size() > 32) {
    res.code = 400;
    res.write("Too Many Minterms");
    res.end();
    return;
  }

  vector<Implicant> primeImplicants = generatePrimeImplicants(minTerms);

  vector<Implicant> essentialPrimeImplicants =
      generateEssentialPrimeImplicants(primeImplicants);

  string EPIsString = "";
  for (auto &implicant : essentialPrimeImplicants) {
    EPIsString += implicantToString(implicant, uniqueVariables);

    if (&implicant != &essentialPrimeImplicants.back()) {
      EPIsString += " + ";
    }
  }

  if (EPIsString == "") {
    if (minTerms.size() == 0) {
      EPIsString = "0";
    } else {
      if (primeImplicants.size() == 1 &&
          implicantToString(primeImplicants[0], uniqueVariables) == "") {
        EPIsString = "1";
      } else {
        EPIsString = "No Essential Prime Implicants";
      }
    }
  }

  inja::Environment env;
  inja::Template PITemplate =
      env.parse_template("templates/essential_prime_implicants.html");

  string result = env.render(PITemplate, {{"EPIs", EPIsString}});

  res.set_header("Content-Type", "text/html");
  res.write(result);
  res.end();

  return;
}