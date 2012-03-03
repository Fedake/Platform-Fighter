#define SFML_DYNAMIC
#include "App.h"

int main(int argc, char *argv[])
{
    App app(600, 400, false);
    app.Run();

    return 0;
}