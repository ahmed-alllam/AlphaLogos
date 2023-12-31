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
#include "../src/qm/essential_prime_implicants.h"
#include "../src/qm/uncovered_minterms.h"

using namespace std;

int calculate_number_of_MOSFETS(vector<Implicant> minimizedImplicants) {
  int numMOSFET = 0;
  int non_zero_PI = 0;

  for (auto &implicant : minimizedImplicants) {
    int num_inputs = 0;

    bool is_zero_PI = true;
    for (auto &literal : implicant.binary) {
      if (literal != -1) {
        num_inputs++;

        if (is_zero_PI) {
          non_zero_PI++;
          is_zero_PI = false;
        }
      }
    }

    if (num_inputs > 1) {
      numMOSFET += num_inputs * 2 + 2;  // AND gate
    }
  }

  if (minimizedImplicants.size() > 1 && non_zero_PI > 1) {
    return numMOSFET + non_zero_PI * 2 + 2;  // OR gate
  }

  return numMOSFET;
}

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

  vector<Implicant> minimizedImplicants = doPetrickMinimization(
      primeImplicants, essentialPrimeImplicants, uncoveredMinterms);

  string minimizedImplicantsString = "";
  for (auto &implicant : minimizedImplicants) {
    minimizedImplicantsString += implicantToString(implicant, uniqueVariables);

    if (&implicant != &minimizedImplicants.back()) {
      minimizedImplicantsString += " + ";
    }
  }

  int numMOSFET = calculate_number_of_MOSFETS(minimizedImplicants);

  if (minimizedImplicantsString == "") {
    numMOSFET = 0;
  }

  if (minimizedImplicantsString == "") {
    if (minTerms.size() == 0) {
      minimizedImplicantsString = "0";
    } else {
      minimizedImplicantsString = "1";
    }
  }

  inja::Environment env;
  inja::Template petrickTemplate = env.parse_template("templates/petrick.html");

  string result =
      env.render(petrickTemplate,
                 {{"minimizedImplicantsString", minimizedImplicantsString},
                  {"numMOSFET", numMOSFET}});

  res.set_header("Content-Type", "text/html");
  res.write(result);
  res.end();

  return;
}