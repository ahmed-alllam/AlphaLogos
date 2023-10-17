#include <crow.h>
#include <Jinja2CppLight/Jinja2CppLight.h>

#include <iostream>

using namespace std;
using namespace Jinja2CppLight;


int main()
{
    crow::SimpleApp app;

    CROW_ROUTE(app, "/")([](){
        return "Hello world";
    });

    app.port(8000).multithreaded().run();

    std::cout << "Hello World";

    Template mytemplate( R"d(
        This is my {{avalue}} template.  It's {{secondvalue}}...
        Today's weather is {{weather}}.
    )d" );

    mytemplate.setValue( "avalue", 3 );
    mytemplate.setValue( "secondvalue", 12.123f );
    mytemplate.setValue( "weather", "rain" );
    string result = mytemplate.render();
    cout << result << endl;
    string expectedResult = R"d(
        This is my 3 template.  It's 12.123...
        Today's weather is rain.
    )d";

}
