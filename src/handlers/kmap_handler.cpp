#include "kmap_handler.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "../logic_utils/canonical_forms.h"
#include "../logic_utils/maxterm.h"
#include "../logic_utils/minterm.h"
#include "../logic_utils/token.h"
#include "../logic_utils/truth_table_generator.h"
#include "../qm/essential_prime_implicants.h"
#include "../qm/implicant.h"
#include "../qm/kmap.h"
#include "../qm/petrick.h"
#include "../qm/prime_implicants.h"
#include "../qm/uncovered_minterms.h"

using namespace std;

string generate_kmap(vector<Implicant> primeImplicants,
                     vector<Token> variableTokens, vector<Minterm> minterms) {
  string kmapLaTeX = makeKMapLaTeX(primeImplicants, variableTokens, minterms);

  ofstream kmapFile;
  string randomString = to_string(rand());
  kmapFile.open("kmap" + randomString + ".tex");
  kmapFile << kmapLaTeX;
  kmapFile.close();

  string command =
      "pdflatex kmap" + randomString + ".tex" + " > /dev/null 2>&1";

  int result = system(command.c_str());

  if (result != 0) {
    throw "Error generating Karnaugh map";
  }

  command = "inkscape kmap" + randomString + ".pdf --export-plain-svg=kmap" +
            randomString + ".svg" + " > /dev/null 2>&1";

  result = system(command.c_str());

  if (result != 0) {
    throw "Error generating Karnaugh map";
  }

  ifstream kmapSVGFile;
  kmapSVGFile.open("kmap" + randomString + ".svg");
  string kmapSVG((istreambuf_iterator<char>(kmapSVGFile)),
                 istreambuf_iterator<char>());

  command = "rm kmap" + randomString + ".tex kmap" + randomString +
            ".pdf kmap" + randomString + ".svg" + " > /dev/null 2>&1";
  result = system(command.c_str());

  return kmapSVG;
}

void kmap_handler(const crow::request &req, crow::response &res) {
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

  if (uniqueVariables.size() > 4 || uniqueVariables.size() < 2) {
    res.code = 400;
    res.write("Number of variables must be between 2 and 4");
    res.end();
    return;
  }

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

  string result = "";

  try {
    result = generate_kmap(minimizedImplicants, uniqueVariables, minTerms);
  } catch (const char *e) {
    res.code = 400;
    res.write("Error generating Karnaugh map");
    res.end();
    return;
  }

  res.set_header("Content-Type", "image/svg+xml");
  res.write(result);
  res.end();

  return;
}
