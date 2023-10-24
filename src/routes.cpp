#include "routes.h"

#include "handlers/main_handler.h"
#include "handlers/validation_handler.h"

void setup_routers(crow::SimpleApp& app) {
  CROW_ROUTE(app, "/").methods(crow::HTTPMethod::Get)(
      [](const crow::request& req, crow::response& res) {
        main_handler(req, res);
      });

  // route for validation
  CROW_ROUTE(app, "/validate")
      .methods(crow::HTTPMethod::Post)(
          [](const crow::request& req, crow::response& res) {
            validation_handler(req, res);
          });
}
