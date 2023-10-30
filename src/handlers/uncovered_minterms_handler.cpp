#include "uncovered_minterms_handler.h"

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
#include "../qm/uncovered_minterms.h"

using namespace std;

void uncovered_minterms_handler(const crow::request &req, crow::response &res) {
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

  vector<Minterm> uncoveredMinterms =
      getUncoveredMinterms(minTerms, essentialPrimeImplicants);

  string uncoveredMintermsString =
      canonicalSoPToString(uncoveredMinterms, uniqueVariables);

  if (uncoveredMintermsString == "") {
    uncoveredMintermsString = "No Uncovered Minterms";
  }

  inja::Environment env;
  inja::Template uncoveredMintermsTemplate =
      env.parse_template("templates/uncovered_minterms.html");

  string result = env.render(uncoveredMintermsTemplate,
                             {{"uncoveredMinterms", uncoveredMintermsString}});

  res.set_header("Content-Type", "text/html");
  res.write(result);
  res.end();

  return;
}