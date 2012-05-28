#define SFML_DYNAMIC
#define WIN32_LEAN_AND_MEAN
#define PF_DEBUG
#include "App.h"
#include "windows.h"

int main(int argc, char *argv[])
{
	std::string arg1;
	if(argv[1] != NULL) arg1 = argv[1];

#ifndef PF_DEBUG
	if(arg1 == "fed")
#endif
	{
		App app(800, 600, false);
		app.Run();
	}
#ifndef PF_DEBUG
	else
	{
		MessageBox(NULL, "Run launcher first!", "Error", MB_OK);
		return 1;
	}
#endif
    return 0;
}