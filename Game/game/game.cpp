// Includes:

// Game:
#include "game.h"
//#include "graphics/graphics.h"

// STL:
#include <stdexcept>
#include <iostream>

// C STDLIB:
#include <cstddef>

namespace game
{
	// Classes:

	// application:

	// Constructor(s):
	application::application(const app_arguments& argData, const display::windowMode& videoInfo, bool autoexec) : args(argData), video(videoInfo)
	{
		if (autoexec)
		{
			execute();
		}
	}

	void application::initializeGraphics(graphics::context& graphicsContext, graphics::contextInfo& renderInfo, bool initGL)
	{
		// Initialize OpenGL if requested:
		if (initGL)
		{
			graphics::configureGL();
		}

		// Create an OpenGL context.
		graphicsContext = SDL_GL_CreateContext(this->window);

		graphics::getContextInfo(renderInfo);

		if (graphicsContext == graphics::nocontext)
		{
			throw std::runtime_error("Unable to create graphical context.");
		}

		if (initGL)
		{
			if (!graphics::initializeGL())
			{
				throw std::runtime_error("Unable to initialize OpenGL.");
			}
		}

		return;
	}

	void application::deinitializeGraphics(graphics::context& graphicsContext, bool deinitGL)
	{
		// Destroy our OpenGL context.
		SDL_GL_DeleteContext(graphicsContext);

		graphicsContext = graphics::nocontext;

		if (deinitGL)
		{
			graphics::deinitializeGL();
		}

		return;
	}

	void application::onCreate(const graphics::context& graphicsContext, const graphics::contextInfo& renderInfo)
	{
		// Temporary vertex shader source code:
		std::string vShaderSource = utilities::load_string("default_vert.glsl");
		std::string fShaderSource = utilities::load_string("default_frag.glsl");

		std::vector<GLfloat> vertexData =
		{
			0.5f,  0.5f, 0.0f,  // Top Right
			0.5f, -0.5f, 0.0f,  // Bottom Right
			-0.5f, -0.5f, 0.0f,  // Bottom Left
			-0.5f,  0.5f, 0.0f   // Top Left
		};

		std::vector<GLuint> indexData =
		{
			0, 1, 3,
			1, 2, 3
		};

		GLchar shaderLog[512];

		if (!defaultShader.build(vShaderSource, fShaderSource, shaderLog, 512))
		{
			std::cout << "Failed to build shader:" << std::endl;

			std::cout << shaderLog;
		}

		testVAO.init(vertexData, GL_STATIC_DRAW, indexData, GL_STATIC_DRAW);
		//testVAO.init(graphics::vertexBufferObject(vertexData, GL_STATIC_DRAW), graphics::elementBufferObject(indexData, GL_STATIC_DRAW));

		// Set the default clear-color.
		//glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		return;
	}

	bool application::onClose()
	{
		// Check if we've done this before:
		if (closed)
		{
			// We've already closed, tell the user.
			return false;
		}

		// Close our window:
		display::destroyWindow(window);
		window = display::systemWindow();

		// Mark this application as 'closed'.
		closed = true;

		// Return the default response.
		return true; // closed;
	}

	// Methods:
	int application::execute()
	{
		// Set up our main window:
		this->window = display::createWindow(this->video);

		if (!display::windowExists(this->window))
		{
			throw std::runtime_error("Unable to create window.");
		}

		// Graphical context:
		graphics::context graphicsContext = {};
		graphics::contextInfo renderInfo = {};

		// Initialize graphical functionality:
		initializeGraphics(graphicsContext, renderInfo);

		// Set the swap-interval.
		SDL_GL_SetSwapInterval(video.vsync);

		// Initialize the application.
		onCreate(graphicsContext, renderInfo);

		try
		{
			// Main application loop:
			while (running()) // <-- Make sure we're still running.
			{
				// Update the application.
				onUpdate();

				// Perform any graphical operations.
				onRender(graphicsContext, renderInfo);

				// Handle incoming events.
				handleEvents();
			}
		}
		catch (std::exception& e)
		{
			// An unhandled exception occurred, perform local cleanup, then re-throw:
			deinitializeGraphics(graphicsContext);

			throw e;
		}

		// Deinitialize graphical behavior.
		deinitializeGraphics(graphicsContext);

		// Close the application.
		onClose();

		return 0;
	}

	void application::onUpdate()
	{
		using namespace std;

		//cout << "Hello world." << endl;

		return;
	}

	void application::onRender(const graphics::context& graphicsContext, const graphics::contextInfo& renderInfo)
	{
		using namespace game::graphics;

		auto vertexPos2DLocation = defaultShader.getAttribute("LVertexPos2D");
		
		glViewport(0, 0, video.width, video.height);
		
		glClearColor(0.2f, 0.2f, 0.3f, 1.0f);
		//glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		glClear(GL_COLOR_BUFFER_BIT);

		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		defaultShader.bind();

		testVAO.draw();

		defaultShader.unbind();

		SDL_GL_SwapWindow(window);

		return;
	}

	void application::onResize(displaySize_t width, displaySize_t height)
	{
		video.width = width;
		video.height = height;

		return;
	}

	bool application::onUnhandledEvent(const systemEvent & e)
	{
		using namespace std;

		cout << "Unhandled event: " << e.type << endl;

		return false;
	}

	void application::handleEvents()
	{
		using namespace std;

		systemEvent e;

		while (SDL_PollEvent(&e))
		{
			switch (e.type)
			{
				case SDL_WINDOWEVENT:
					switch (e.window.event)
					{
						case SDL_WINDOWEVENT_RESIZED:
							#ifdef GAME_CONSOLE
								cout << "Window resized: " << e.window.data1 << "x" << e.window.data2 << endl;
							#endif

							onResize(e.window.data1, e.window.data2);

							break;
					}

					break;
				case SDL_MOUSEBUTTONDOWN:
					cout << "Mouse button detected: " << e.button.button << endl;

					break;
				case SDL_KEYDOWN:
					cout << "Keyboard button detected: " << e.key.keysym.sym << endl;

					break;
				case SDL_QUIT:
					signalClose();

					return; // break;
				default:
					onUnhandledEvent(e);

					break;
			}
		}

		return;
	}

	// app_arguments:
	app_arguments::app_arguments(std::size_t argc, const char** argv)
	{
		data = std::vector<std::string>(argc);

		for (auto i = 0; i < argc; i++)
		{
			data[i] = std::string(argv[i]);
		}
	}

	app_arguments::app_arguments(std::vector<std::string> values) : data(values)
	{
		// Nothing so far.
	}

	// Functions:
	// Nothing so far.
}