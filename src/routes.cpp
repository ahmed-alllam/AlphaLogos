#include "routes.h"

#include "handlers/canonicals_handler.h"
#include "handlers/circuit_drawer_handler.h"
#include "handlers/kmap_handler.h"
#include "handlers/main_handler.h"
#include "handlers/prime_implicants_handler.h"
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

  CROW_ROUTE(app, "/PI")
      .methods(crow::HTTPMethod::Post)(
          [](const crow::request &req, crow::response &res) {
            prime_implicants_handler(req, res);
          });

  CROW_ROUTE(app, "/draw-circuit")
      .methods(crow::HTTPMethod::Post)(
          [](const crow::request &req, crow::response &res) {
            circuit_drawer_handler(req, res);
          });

  CROW_ROUTE(app, "/draw-kmap")
      .methods(crow::HTTPMethod::Post)(
          [](const crow::request &req, crow::response &res) {
            kmap_handler(req, res);
          });
}
