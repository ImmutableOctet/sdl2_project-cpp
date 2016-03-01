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
	// Typedefs:
	using displaySize_t = int;
	using windowCoordinate_t = int;

	namespace display
	{
		// Typedefs:
		using systemWindow = SDL_Window*;

		using size_t = displaySize_t;
		using coordinate_t = windowCoordinate_t;

		// Structures:
		struct displayMode
		{
			// Typedefs:
			using size_t = displaySize_t;

			size_t width = SDL_WINDOWPOS_UNDEFINED;
			size_t height = SDL_WINDOWPOS_UNDEFINED;
		};

		struct windowMode : displayMode
		{
			// Typedefs:
			//using coordinate_t = windowCoordinate_t;

			coordinate_t x = SDL_WINDOWPOS_UNDEFINED;
			coordinate_t y = SDL_WINDOWPOS_UNDEFINED;

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
