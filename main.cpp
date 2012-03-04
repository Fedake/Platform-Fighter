#define SFML_DYNAMIC
#include "App.h"

int main(int argc, char *argv[])
{
    App app(800, 600, false);
    app.Run();

    return 0;
}