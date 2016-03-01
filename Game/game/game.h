#pragma once

// Includes:

// Local:
#include "config.h"
#include "display.h"
#include "graphics/graphics.h"

// Libraries:

// SDL:
#include <SDL.h>

// CSTDLIB:
#include <cstddef>

// STL:
#include <vector>
#include <string>
#include <utility>

namespace game
{
	// Typedefs:
	using systemEvent = SDL_Event;

	struct app_arguments
	{
		app_arguments(std::size_t argc, const char** argv);
		app_arguments(std::vector<std::string> data);

		std::vector<std::string> data;
	};

	class application
	{
		public:
			// Constructor(s):

			// The 'autoexec' argument is used to automatically call 'execute'.
			application(const app_arguments& args, const display::windowMode& video, bool autoexec=false);

			// Destructor(s):
			//~application();

			// Methods:

			// This executes the application.
			// This is called if 'autoexec' is enabled in a constrcutor.
			int execute();

			// This returns a reference to the arguments used to start this application.
			// Use this command at your own risk.
			inline const app_arguments& getArgs() const
			{
				return args;
			}

			// This retrieves the main window associated with this application.
			inline const display::systemWindow getWindow() const
			{
				return window;
			}

			// This states if this application is running normally.
			inline bool running() const
			{
				return (!closed);
			}

			/*
				This starts the closure process.
				
				This should not be confused with 'onClose', which is
				called automatically when the application is ready to exit.
			*/

			inline void signalClose()
			{
				closed = true;

				return;
			}

			/*
				This instantly calls 'onClose', without any warning or proper practice.
				
				It's best to only call this if an uncaught exception occurred,
				but you want to attempt to gracefully close this application.
			*/

			inline void forceClose()
			{
				onClose();

				return;
			}
		protected:
			// Methods:

			// This automatically calls 'initializeGL' if 'initGL' is 'true'.
			void initializeGraphics(graphics::context& graphicsContext_out, graphics::contextInfo& renderInfo_out, bool initGL=true);

			// This should be called when graphical behavior is no longer needed.
			// The 'deinitGL' argument is currently reserved.
			void deinitializeGraphics(graphics::context& graphicsContext, bool deinitGL=true);

			virtual void onCreate(const graphics::context& graphicsContext_out, const graphics::contextInfo& renderInfo_out);
			virtual bool onClose();

			virtual void onUpdate();
			virtual void onRender(const graphics::context& graphicsContext, const graphics::contextInfo& renderInfo);
			virtual void onResize(displaySize_t width, displaySize_t height);
			virtual bool onUnhandledEvent(const systemEvent& e);

			void handleEvents();

			// Fields:
			app_arguments args;

			display::systemWindow window;
			display::windowMode video;

			graphics::shader defaultShader;

			graphics::vertexArrayObject testVAO;

			bool closed = false;
	};
}