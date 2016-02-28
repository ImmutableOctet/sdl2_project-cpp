// Includes:

// Game:
#include "game.h"
//#include "graphics/graphics.h"

// STL:
#include <stdexcept>
#include <iostream>
#include <vector>

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
		renderInfo = {};

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
		const GLchar* vShaderSource = "#version 330 core\n"
										"layout (location = 0) in vec3 position;\n"
										"void main()\n"
										"{\n"
											"gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
										"}\0";
		const GLchar* fShaderSource = "#version 330 core\n"
										"out vec4 color;\n"
										"void main()\n"
										"{\n"
											"color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
										"}\n\0";

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

		auto shaderInstance = graphics::shader(vShaderSource, fShaderSource);

		if (shaderInstance == graphics::shader::noinstance)
		{
			throw std::runtime_error("Unable to build test shader.");
		}

		GLchar shaderLog[512];

		if (!defaultShader.build(vShaderSource, fShaderSource, shaderLog, 512))
		{
			std::cout << "Failed to build shader:" << std::endl;

			std::cout << shaderLog;
		}

		defaultShader = std::move(shaderInstance);

		auto vertices = graphics::vertexBufferObject(vertexData, GL_STATIC_DRAW);
		auto indices = graphics::elementBufferObject(indexData, GL_STATIC_DRAW);

		testVAO = graphics::vertexArrayObject(std::move(vertices), std::move(indices));

		// Set the default clear-color.
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

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

		//glViewport(0, 0, video.width, video.height);
		glClearColor(0.2f, 0.2f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(defaultShader.getInstance());

		glBindVertexArray(testVAO.getInstance());

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

		glBindVertexArray(vertexArrayObject::noinstance);

		/*
		glEnableVertexAttribArray(vertexPos2DLocation);

		glBindBuffer(GL_ARRAY_BUFFER, testVertices[0]);
		glVertexAttribPointer(vertexPos2DLocation, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), NULL);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, testIndices[0]);
		glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, NULL);

		glDisableVertexAttribArray(vertexPos2DLocation);
		*/

		glUseProgram(NULL);

		SDL_GL_SwapWindow(window);

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
		systemEvent e;

		while (SDL_PollEvent(&e))
		{
			switch (e.type)
			{
				case SDL_MOUSEBUTTONDOWN:
					// Nothing so far.

					break;
				case SDL_KEYDOWN:
					// Nothing so far.

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