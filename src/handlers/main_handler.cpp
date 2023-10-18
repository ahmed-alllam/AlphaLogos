#include "main_handler.h"

using namespace std;

void main_handler(const crow::request& req, crow::response& res) {

    Jinja2CppLight::Template mytemplate( R"d(
        This is my {{avalue}} template.  It's {{secondvalue}}...
        Today's weather is {{weather}}.
    )d" );

    mytemplate.setValue( "avalue", 3 );
    mytemplate.setValue( "secondvalue", 12.123f );
    mytemplate.setValue( "weather", "rain" );
    string result = mytemplate.render();

    res.set_header("Content-Type", "text/html");
    res.write(result);
    res.end();
}