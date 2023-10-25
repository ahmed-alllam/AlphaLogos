#include "circuit_drawer_handler.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "../logic_utils/canonical_forms.h"
#include "../logic_utils/circuit_drawer.h"
#include "../logic_utils/maxterm.h"
#include "../logic_utils/minterm.h"
#include "../logic_utils/token.h"
#include "../logic_utils/truth_table_generator.h"

using namespace std;

string verilogToJSON(string verilogCode) {
  ofstream tempFile;
  string randomString = to_string(rand());
  tempFile.open("temp" + randomString + ".v");
  tempFile << verilogCode;
  tempFile.close();

  string command = "./yosys2digitaljs/process.js temp" + randomString +
                   ".v > temp" + randomString + ".v.json";
  int result = system(command.c_str());

  if (result != 0) {
    cerr << "Failed to parse verilog code" << endl;
    return "";
  }

  ifstream jsonFile;
  jsonFile.open("temp" + randomString + ".v.json");

  string jsonCode = "";
  string line;
  while (getline(jsonFile, line)) {
    jsonCode += line;
  }

  jsonFile.close();

  // remove the temporary files
  command =
      "rm temp" + randomString + ".v" + " temp" + randomString + ".v.json";
  result = system(command.c_str());

  if (result != 0) {
    cerr << "Failed to remove temporary files" << endl;
    return "";
  }

  return jsonCode;
}

void circuit_drawer_handler(const crow::request &req, crow::response &res) {
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
  //   vector<Token> uniqueVariables = getUniqueVariables(tokens);
  //   vector<vector<bool>> truthTable = generateTruthTable(tokens);
  //   vector<Minterm> minTerms = generateMinTerms(uniqueVariables, truthTable);

  // We should get the minimized expression from the qm. But since it is yet to
  // be implemented, we will just use the original expression.

  string verilogCode = SoPToVerilog(tokens);
  string result = verilogToJSON(verilogCode);

  if (result == "") {
    res.code = 400;
    res.write("Failed to parse verilog.");
    res.end();
    return;
  }

  res.write(result);
  res.end();

  return;
}