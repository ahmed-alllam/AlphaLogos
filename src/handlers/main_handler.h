#ifndef MAIN_HANDLER_H
#define MAIN_HANDLER_H

#include <crow.h>

#include "Jinja2CppLight/Jinja2CppLight.h"

void main_handler(const crow::request& req, crow::response& res);

#endif  // MAIN_HANDLER_H
