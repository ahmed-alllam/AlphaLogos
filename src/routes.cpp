#include "routes.h"

#include "handlers/canonicals_handler.h"
#include "handlers/main_handler.h"
#include "handlers/truth_table_handler.h"
#include "handlers/validation_handler.h"

void setup_routers(crow::SimpleApp &app) {
  CROW_ROUTE(app, "/").methods(crow::HTTPMethod::Get)(
      [](const crow::request &req, crow::response &res) {
        main_handler(req, res);
      });

  CROW_ROUTE(app, "/validate")
      .methods(crow::HTTPMethod::Post)(
          [](const crow::request &req, crow::response &res) {
            validation_handler(req, res);
          });

  CROW_ROUTE(app, "/truth-table")
      .methods(crow::HTTPMethod::Post)(
          [](const crow::request &req, crow::response &res) {
            truth_table_handler(req, res);
          });

  CROW_ROUTE(app, "/canonicals")
      .methods(crow::HTTPMethod::Post)(
          [](const crow::request &req, crow::response &res) {
            canonicals_handler(req, res);
          });
}
