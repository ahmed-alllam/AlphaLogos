#include "main_handler.h"

#include <fstream>
#include <iostream>

using namespace std;

void main_handler(const crow::request& req, crow::response& res) {
  ifstream template_file("templates/index.html");

  string homePage = string(istreambuf_iterator<char>(template_file),
                           istreambuf_iterator<char>());

  Jinja2CppLight::Template homePageTemplate(homePage);

  string result = homePageTemplate.render();

  res.set_header("Content-Type", "text/html");
  res.write(result);
  res.end();
}