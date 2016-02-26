// Includes:
#include "display.h"

#include <SDL.h>

// Namespace(s):
namespace game
{
	namespace display
	{
		// Functions:
		systemWindow createWindow(const windowMode& mode)
		{
			return SDL_CreateWindow
			(
				mode.title.c_str(),
				mode.x,
				mode.y,
				mode.width,
				mode.height,
				mode.flags
			);
		}

		void destroyWindow(systemWindow window)
		{
			// Close and destroy the window.
			SDL_DestroyWindow(window);

			return;
		}

		bool windowExists(systemWindow window)
		{
			return (window != nullptr);
		}
	}
}