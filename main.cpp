#define SFML_DYNAMIC
#define WIN32_LEAN_AND_MEAN
#include "App.h"
#include "windows.h"

int main(int argc, char *argv[])
{
	std::string arg1;
	if(argv[1] != NULL) arg1 = argv[1];

	if(arg1 == "fed")
	{
		App app(800, 600, false);
		app.Run();
	}
	else
	{
		MessageBox(NULL, "Run launcher first!", "Error", MB_OK);
		return 1;
	}
    return 0;
}