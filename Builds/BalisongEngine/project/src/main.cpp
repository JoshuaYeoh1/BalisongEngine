#include "Application.h"
using namespace BalisongEngine;
using namespace BalisongEngineFramework;

// ====================================================================

int main()
{
	Application app;

	int result = app.Init(1280, 720, "Balisong Engine");

	if (result == 1)
	{
		app.SetTargetFrameRate(60); // optional
		app.Run();
		app.CleanUp();
	}
}