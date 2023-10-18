#include "main_handler.h"

#include <fstream>
#include <iostream>

using namespace std;

void main_handler(const crow::request& req, crow::response& res) {

    ifstream template_file("templates/index.html");

    string template_string = string(istreambuf_iterator<char>(template_file), istreambuf_iterator<char>());
    
    Jinja2CppLight::Template mytemplate(template_string);

    string result = mytemplate.render();

    res.set_header("Content-Type", "text/html");
    res.write(result);
    res.end();
}