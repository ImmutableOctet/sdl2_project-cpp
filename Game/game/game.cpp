// Includes:

// Game:
#include "game.h"
//#include "graphics/graphics.h"

// STL:
#include <stdexcept>
#include <iostream>
//#include <chrono>

// C STDLIB:
#include <cstddef>
#include <cmath>

// GLM:
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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
		static const auto MODE_FULL = 0;
		static const auto MODE_DEFAULT = 1;

		const auto mode = MODE_DEFAULT;

		// Temporary vertex shader source code:
		std::string vShaderSource;
		std::string fShaderSource;
		
		switch (mode)
		{
			case MODE_DEFAULT:
				vShaderSource = utilities::load_string("shaders/default_vert.glsl");
				fShaderSource = utilities::load_string("shaders/default_frag.glsl");

				break;
			case MODE_FULL:
				vShaderSource = utilities::load_string("shaders/full/vert.glsl");
				fShaderSource = utilities::load_string("shaders/full/frag.glsl");

				break;
		}

		GLchar shaderLog[512] = {};

		if (!defaultShader.build(vShaderSource, fShaderSource, shaderLog, 512))
		{
			std::cout << "Failed to build shader:" << std::endl;

			std::cout << shaderLog;
		}

		switch (mode)
		{
			case MODE_DEFAULT:
				{
					std::vector<GLfloat> vertexData =
					{
						-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
						0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
						0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
						0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
						-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
						-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

						-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
						0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
						0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
						0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
						-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
						-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

						-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
						-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
						-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
						-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
						-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
						-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

						0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
						0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
						0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
						0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
						0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
						0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

						-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
						0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
						0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
						0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
						-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
						-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

						-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
						0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
						0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
						0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
						-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
						-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
					};

					testVAO.init(vertexData, 36, GL_STATIC_DRAW, false, false, true);
				}

				break;
			case MODE_FULL:
				{
					using vertex = graphics::vertex_t;

					std::vector<vertex> vertexData =
					{
						// Positions:					// Colors:			// Texture UVs:
						{ { 0.5f,  0.5f, 0.0f },	{ 1.0f, 1.0f, 1.0f, 0.0f },	{ 4.0f, 4.0f } },	// Top, right
						{ { 0.5f, -0.5f, 0.0f },	{ 1.0f, 1.0f, 1.0f, 1.0f },	{ 4.0f, 0.0f } },	// Bottom, right
						{ { -0.5f, -0.5f, 0.0f },	{ 1.0f, 1.0f, 1.0f, 0.7f },	{ 0.0f, 0.0f } },	// Bottom, left
						{ { -0.5f,  0.5f, 0.0f },	{ 1.0f, 1.0f, 1.0f, 0.0f },	{ 0.0f, 4.0f } }	// Top, left
					};

					std::vector<GLuint> indexData =
					{
						0, 1, 3,
						1, 2, 3
					};

					testVAO.init(vertexData, vertexData.size(), GL_STATIC_DRAW, indexData, GL_STATIC_DRAW, true, true, true);
					//testVAO.init(vertexData, GL_STATIC_DRAW, true, true, true);
				}

				break;
		}

		// Load some textures:
		const char* texturePaths[] =
		{
			"01.png", "02.png"
		};

		for (auto i = 0; i < testTextures.size(); i++)
		{
			testTextures[i].load(texturePaths[i], true);
		}

		// Set the default clear-color.
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		// Initialize our camera.
		testCamera = graphics::camera(glm::vec3(0.0f, 0.0f, -8.0f), glm::vec2(0.0f, -90.0f)); // graphics::camera(glm::vec3(0.0f, 0.0f, -8.0f));

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
		
		static const std::vector<glm::vec3> positions =
		{
			{ 0.0f, 0.0f, 0.0f },
			{ 2.0f, 5.0f, -15.0f },
			{ -1.5f, -2.2f, -2.5f },
			{ -3.8f, -2.0f, -12.3f },
			{ 2.4f, -0.4f, -3.5f },
			{ -1.7f, 3.0f, -7.5f },
			{ 1.3f, -2.0f, -2.5f },
			{ 1.5f, 2.0f, -2.5f },
			{ 1.5f, 0.2f, -1.5f },
			{ -1.3f, 1.0f, -1.5f }
		};

		glEnable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDepthFunc(GL_LESS);

		glViewport(0, 0, video.width, video.height);

		glClearColor(0.0f, 0.6f, 0.4f, 1.0f);
		//glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		// Start using 'defaultShader'.
		defaultShader.bind();

		const auto shaderInst = defaultShader.getInstance();

		glm::mat4 view;
		glm::mat4 projection;

		// Move the camera backward.
		view = testCamera.getViewMatrix();
		//view = glm::translate(view, glm::vec3(0.0f, 0.0f, -8.0f));


		// Set the projection area:
		projection = testCamera.getProjectionMatrixFrom(video.width, video.height, 0.1f, 1000.0f);
		//projection = glm::perspective(glm::radians(45.0f), static_cast<GLfloat>(video.width) / static_cast<GLfloat>(video.height), 0.1f, 2000.0f);

		// Get the locations of our vertices in 'shaderInst' 
		auto modelLocation = glGetUniformLocation(shaderInst, "model");
		auto viewLocation = glGetUniformLocation(shaderInst, "view");
		auto projLocation = glGetUniformLocation(shaderInst, "projection");

		// Upload the texture mix-value:
		setUniform(glGetUniformLocation(shaderInst, "mix_value"), 0.4f);

		// Upload our main matrices:
		glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLocation, 1, GL_FALSE, glm::value_ptr(projection));

		// Bind and register our textures:
		for (GLint i = 0; i < testTextures.size(); i++)
		{
			glActiveTexture(GL_TEXTURE0 + i);
			testTextures[i].bind();

			setUniform(glGetUniformLocation(shaderInst, (std::string("textureHandle_") + std::to_string(i)).c_str()), i);
		}

		// Rending some objects:

		// Bind the test-VAO.
		testVAO.bind();

		for (GLuint i = 0; i < positions.size(); i++)
		{
			// Build a model matrix:
			glm::mat4 model;

			model = glm::translate(model, positions[i]);

			GLfloat angle = 20.0f * (i+1);

			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));

			// Upload our built matrix.
			glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));

			// Draw our model.
			testVAO.draw(GL_TRIANGLES, false);
		}

		// Unbind our test-VAO.
		testVAO.unbind();

		// Unbind our textures:
		for (auto i = 0; i < testTextures.size(); i++)
		{
			glActiveTexture(GL_TEXTURE0 + i);
			testTextures[i].unbind();
		}

		// Stop using 'defaultShader'.
		defaultShader.unbind();

		// Disable depth-testing.
		glDisable(GL_DEPTH_TEST);

		// Disable blending.
		glDisable(GL_BLEND);

		// Flip the front and back buffers.
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
					cout << "Mouse button detected: " << static_cast<int>(e.button.button) << endl;

					break;
				case SDL_KEYDOWN:
					cout << "Keyboard button detected: " << e.key.keysym.sym << endl;

					testCamera.getPosition().z -= 0.1f;

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