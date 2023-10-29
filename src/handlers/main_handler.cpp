#include "main_handler.h"

#include <fstream>
#include <iostream>

#include <inja.hpp>

using namespace inja;
using namespace std;

void main_handler(const crow::request& req, crow::response& res) {
  Environment env;
  Template homePageTemplate = env.parse_template("templates/index.html");

  string result = env.render(homePageTemplate, {});

  res.set_header("Content-Type", "text/html");
  res.write(result);
  res.end();
}