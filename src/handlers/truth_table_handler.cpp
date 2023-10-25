#include "truth_table_handler.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "../logic_utils/token.h"
#include "../logic_utils/truth_table_generator.h"
#include "Jinja2CppLight/Jinja2CppLight.h"

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

  ifstream truth_table_template_file("templates/truth_table.html");

  string truth_table_string =
      string(istreambuf_iterator<char>(truth_table_template_file),
             istreambuf_iterator<char>());

  Jinja2CppLight::Template truth_table_template(truth_table_string);

  if (tokens.size() == 0) {
    res.code = 400;
    res.write("Invalid expression");
    res.end();
    return;
  }

  vector<Token> uniqueVariables = getUniqueVariables(tokens);
  Jinja2CppLight::TupleValue variableNames;

  for (Token token : uniqueVariables) {
    variableNames.addValue(string(1, token.value));
  }

  vector<vector<bool>> truth_table = generateTruthTable(tokens);

  Jinja2CppLight::TupleValue truth_table_tuple;

  for (vector<bool> row : truth_table) {
    Jinja2CppLight::TupleValue row_tuple;

    for (bool value : row) {
      row_tuple.addValue(value);
    }

    truth_table_tuple.addValue(row_tuple);
  }

  truth_table_template.setValue("expression", logic_expression);
  truth_table_template.setValue("variableNames", variableNames);
  truth_table_template.setValue("truth_table", truth_table_tuple);

  string result = truth_table_template.render();

  res.set_header("Content-Type", "text/html");
  res.write(result);
  res.end();

  return;
}