#define SFML_DYNAMIC
#include "App.h"
#include "windows.h"
#define WIN32_LEAN_AND_MEAN

int main(int argc, char *argv[])
{
    App app(800, 600, false);
	app.Run();

    return 0;
}