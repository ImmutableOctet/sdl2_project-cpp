// Includes:
#include "game/game.h"

#include <iostream>
#include <stdexcept>

#ifdef GAME_CONSOLE
	#include <cstdio>

	#ifdef PLATFORM_WINDOWS
		#define	WIN32_LEAN_AND_MEAN
		
		#include <windows.h>
	#endif
#endif

// Functions:
int main(int argc, char** argv)
{
	// Namespace(s):
	using namespace std;

	using namespace game;
	using namespace game::display;

	#ifdef GAME_CONSOLE // GAME_DEBUG
		#ifdef PLATFORM_WINDOWS
			// Enable the developer-console.
			AllocConsole();
			
			// Connect standard I/O to our console:
			auto conin = freopen("conin$", "r", stdin);
			auto conout = freopen("conout$", "w", stdout);
			auto conerr = freopen("conout$", "w", stderr);
		#endif
	#endif

	// Initialize SDL.
	SDL_Init(SDL_INIT_VIDEO);

	// Local variable(s):
	int responseCode = 0;

	// Create a window-mode:
	windowMode display;

	// Configure the window:
	display.title = "OpenGL Application";
	display.width = 1280; // 960;
	display.height = 720; // 540;
	display.flags |= (SDL_WINDOW_RESIZABLE); // SDL_WINDOW_MAXIMIZED;
	//display.vsync = false;

	application app(app_arguments(argc, (const char**)argv), display);

	try
	{
		// Start the application.
		responseCode = app.execute();
	}
	catch (std::exception& e)
	{
		cout << "Unhandled exception detected:" << endl << e.what() << endl;

		// Force the application to close.
		app.forceClose();

		responseCode = -1; // 1
	}

	// Deinitialize SDL.
	SDL_Quit();

	#ifdef GAME_CONSOLE // GAME_DEBUG
		#ifdef PLATFORM_WINDOWS
			fclose(conin);
			fclose(conout);
			fclose(conerr);
			
			FreeConsole();
		#endif
	#endif

	// Return the calculated response.
	return responseCode;
}