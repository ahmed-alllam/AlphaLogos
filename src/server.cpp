#include "server.h"

#include <crow.h>

#include <string>

#include "routes.h"

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
  if (result != 0) {
    cerr << "Failed to open browser" << endl;
  }
}

void launch_server() {
  crow::SimpleApp app;
  setup_routers(app);

  app.port(8012).multithreaded().run();

  // open_browser("http://localhost:8000"); // ToDo: uncomment this line later
}
