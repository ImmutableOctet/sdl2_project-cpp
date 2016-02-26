// Includes:
#include "graphics.h"

#include <stdexcept>

namespace game
{
	namespace graphics
	{
		// Functions:
		void configureGL()
		{
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1); // 3
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

		// Classes:

		// shader:

		// Functions:
		shaderHandle shader::buildProgram(const GLchar* str, GLenum shaderType)
		{
			// Create a vertex shader.
			shaderHandle shaderInstance = glCreateShader(shaderType);

			// Bind our shader source to 'shaderInstance'.
			glShaderSource(shaderInstance, 1, &str, nullptr);

			// Compile the vertex shader.
			glCompileShader(shaderInstance);

			// This will hold the build status of our shader.
			GLint shaderCompileStatus = GL_FALSE;

			// Check if the shader was compiled:
			glGetShaderiv(shaderInstance, GL_COMPILE_STATUS, &shaderCompileStatus);

			if (shaderCompileStatus != GL_TRUE)
			{
				glDeleteShader(shaderInstance);

				return noinstance;
			}

			return shaderInstance;
		}

		// Constructor(s):
		shader::shader()
		{
			// Nothing so far.
		}

		shader::shader(const std::string& vertex, const std::string& fragment)
		{
			build(vertex, fragment);
		}

		// Destructor(s):
		shader::~shader()
		{
			destroy();
		}

		// Operator overloads:
		shader& shader::operator=(shader&& input)
		{
			this->instance = input.instance;

			return *this;
		}

		// Methods:
		void shader::build(const GLchar* vShaderSource, const GLchar* fShaderSource, shaderHandle* vertex_out, shaderHandle* fragment_out)
		{
			if (exists())
			{
				throw std::runtime_error("Attempted to build an existing shader; please call 'destroy' first.");
			}

			// Allocate a program-handle.
			shaderHandle programID = glCreateProgram();

			// These act as handles for our shaders:
			shaderHandle vertexShader = noinstance;
			shaderHandle fragmentShader = noinstance;

			bool error = false;

			try
			{
				// Build our vertex shader's source code.
				vertexShader = buildProgram(vShaderSource, GL_VERTEX_SHADER);

				if (vertexShader == noinstance)
					throw std::runtime_error("Failed to compile vertex shader.");

				// Attach our compiled vertex shader.
				glAttachShader(programID, vertexShader);

				// Build our fragment shader's source code.
				fragmentShader = buildProgram(fShaderSource, GL_FRAGMENT_SHADER);

				if (fragmentShader == noinstance)
					throw std::runtime_error("Failed to compile fragment shader.");

				// Attach our compiled vertex shader.
				glAttachShader(programID, fragmentShader);

				// Link our shaders into one program.
				glLinkProgram(programID);

				GLint programStatus = GL_TRUE;

				glGetProgramiv(programID, GL_LINK_STATUS, &programStatus);

				if (programStatus != GL_TRUE)
				{
					throw std::runtime_error("Failed to link shader program.");
				}
			}
			catch (std::exception& e)
			{
				error = true;

				glDeleteProgram(programID);

				programID = noinstance;
			}

			if (!error && (fragment_out != nullptr && vertex_out != nullptr))
			{
				*vertex_out = vertexShader;
				*fragment_out = fragmentShader;
			}
			else
			{
				if (vertexShader != noinstance)
				{
					glDeleteShader(vertexShader);
				}

				if (fragmentShader != noinstance)
				{
					glDeleteShader(fragmentShader);
				}

				if (fragment_out != nullptr)
					*fragment_out = noinstance;

				if (vertex_out != nullptr)
					*vertex_out = noinstance;
			}

			// Set the internal program instance.
			this->instance = programID;

			return;
		}

		void shader::destroy()
		{
			if (instance != noinstance)
			{
				glDeleteProgram(instance);
				instance = noinstance;
			}

			return;
		}

		shaderLocation shader::getAttribute(const GLchar* name)
		{
			return static_cast<shaderLocation>(glGetAttribLocation(instance, name));
		}

		bool shader::setFloat(shaderLocation location, GLfloat value)
		{
			glUniform1f(location, value);

			// Return the default response.
			return true;
		}
	}
}