// Includes:
#include "opengl.h"
#include "context.h"

// Namespace(s):
namespace game
{
	namespace graphics
	{
		// Functions:
		void configureGL()
		{
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3); // 1
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

			return;
		}

		bool initializeGL(bool experimental, bool autocfg)
		{
			if (autocfg)
			{
				configureGL();
			}

			// Initialize GLEW:
			glewExperimental = experimental;

			auto errorCode = glewInit();

			if (errorCode != GLEW_OK)
			{
				return false;
			}

			// Return the default response. (Success)
			return true;
		}

		void deinitializeGL()
		{
			// Nothing so far.
		}
	}
}