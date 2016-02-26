#pragma once

// Includes:

// STL:
#include <string>

// SDL:
#include <SDL.h>

// Forward declarations:
//struct SDL_Window;

// Namespace(s):
namespace game
{
	namespace display
	{
		// Typedefs:
		using systemWindow = SDL_Window*;

		// Structures:
		struct displayMode
		{
			int width = SDL_WINDOWPOS_UNDEFINED;
			int height = SDL_WINDOWPOS_UNDEFINED;
		};

		struct windowMode : displayMode
		{
			int x = SDL_WINDOWPOS_UNDEFINED;
			int y = SDL_WINDOWPOS_UNDEFINED;

			bool vsync = true; // int vsync = 1;

			Uint32 flags = (SDL_WINDOW_OPENGL|SDL_WINDOW_SHOWN);

			std::string title;
		};

		// Functions:

		// Window management API:
		systemWindow createWindow(const windowMode& mode);
		void destroyWindow(systemWindow window);

		bool windowExists(systemWindow window);
	}
}
