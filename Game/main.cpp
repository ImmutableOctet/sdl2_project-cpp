// Includes:
#include "game/game.h"

#include <iostream>
#include <stdexcept>

// Functions:
int main(int argc, char** argv)
{
	// Namespace(s):
	using namespace std;

	using namespace game;
	using namespace game::display;

	// Initialize SDL.
	SDL_Init(SDL_INIT_VIDEO);

	// Local variable(s):
	int responseCode = 0;

	// Create a window-mode:
	windowMode display;

	// Configure the window:
	display.title = "Application";
	display.width = 1280;
	display.height = 720;
	display.flags |= (SDL_WINDOW_RESIZABLE); // SDL_WINDOW_MAXIMIZED;

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

	// Return the calculated response.
	return responseCode;
}