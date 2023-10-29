#include "truth_table_handler.h"

#include <fstream>
#include <inja.hpp>
#include <iostream>
#include <string>
#include <vector>

#include "../logic_utils/token.h"
#include "../logic_utils/truth_table_generator.h"

using namespace std;

void truth_table_handler(const crow::request &req, crow::response &res) {
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

  if (tokens.size() == 0) {
    res.code = 400;
    res.write("Invalid expression");
    res.end();
    return;
  }

  inja::Environment env;
  inja::Template truth_table_template =
      env.parse_template("templates/truth_table.html");

  vector<Token> uniqueVariables = getUniqueVariables(tokens);
  vector<string> variableNames;

  for (Token token : uniqueVariables) {
    variableNames.push_back(string(1, token.value));
  }

  vector<vector<bool>> truth_table = generateTruthTable(tokens);

  string result = env.render(truth_table_template,
                             {{"variableNames", variableNames},
                              {"truth_table", truth_table},
                              {"logic_expression", logic_expression}});

  res.set_header("Content-Type", "text/html");
  res.write(result);
  res.end();

  return;
}