#include "validation_handler.h"

#include <fstream>
#include <iostream>

#include "../logic_utils/PoS_validator.h"
#include "../logic_utils/SoP_validator.h"

using namespace std;

void validation_handler(const crow::request& req, crow::response& res) {
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

  if (isValidSoP(logic_expression)) {
    res.code = 200;
    res.write("Valid SoP");
    res.end();
    return;
  }

  if (isValidPoS(logic_expression)) {
    res.code = 200;
    res.write("Valid PoS");
    res.end();
    return;
  }

  res.code = 400;
  res.write("Invalid expression");
  res.end();
  return;
}