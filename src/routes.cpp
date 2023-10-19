#include "routes.h"

#include "handlers/main_handler.h"

void setup_routers(crow::SimpleApp& app) {
  CROW_ROUTE(app, "/").methods(crow::HTTPMethod::Get)(
      [](const crow::request& req, crow::response& res) {
        main_handler(req, res);
      });
}
