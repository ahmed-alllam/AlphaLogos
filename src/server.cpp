#include "server.h"
#include "routes.h"

#include <crow.h>

#include <string>

using namespace std;


void open_browser(string url) {
    string command;

#ifdef _WIN32
    // Windows command
    command = "start " + url;
#elif _WIN64
    command = "start " + url;
#elif __APPLE__
    // macOS command
    command = "open " + url;
#elif __MACH__
    command = "open " + url;
#else
    // Linux command
    command = "xdg-open " + url;
#endif

    int result = system(command.c_str());
    if (result != 0)
    {
        cerr << "Failed to open browser" << endl;
    }
}

void launch_server() {
    crow::SimpleApp app;
    setup_routers(app);

    auto _a = app.port(8000).multithreaded().run_async();
    std::cout << "Server is running on port 8000" << std::endl;

    open_browser("http://localhost:8000");
}
