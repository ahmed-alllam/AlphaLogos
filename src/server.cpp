#include "server.h"
#include "routes.h"

#include <crow.h>

void launch_server() {
    crow::SimpleApp app;
    setup_routers(app);
    app.port(8080).multithreaded().run();
}
