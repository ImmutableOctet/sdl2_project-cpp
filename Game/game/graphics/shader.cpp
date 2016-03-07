// Includes:
#include "shader.h"

#include <utility>
#include <stdexcept>
#include <cstring>

// Namespace(s):
namespace game
{
	namespace graphics
	{
		// shader:

		// Functions:
		shaderHandle shader::buildProgram(const GLchar* str, GLenum shaderType, GLchar* log_out, GLsizei log_maxLength)
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
				if ((log_out != nullptr) && log_maxLength > 0)
				{
					glGetShaderInfoLog(shaderInstance, log_maxLength, nullptr, log_out);
				}

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
			if (!build(vertex, fragment))
			{
				throw std::runtime_error("Failed to compile shader.");
			}
		}

		// Destructor(s):
		shader::~shader()
		{
			destroy();
		}

		// Operator overloads:
		shader::operator resourceHandle_t() const
		{
			return getInstance();
		}

		// Methods:
		bool shader::build(const GLchar* vShaderSource, const GLchar* fShaderSource, GLchar* log_out, GLsizei log_maxLength, shaderHandle* vertex_out, shaderHandle* fragment_out)
		{
			if (exists())
			{
				throw std::runtime_error("Attempted to build an existing shader; please call 'destroy' first.");
			}

			if (log_out != nullptr && log_maxLength == 0)
			{
				log_maxLength = static_cast<GLsizei>(std::strlen((const char*)log_out));
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
				vertexShader = buildProgram(vShaderSource, GL_VERTEX_SHADER, log_out, log_maxLength);

				if (vertexShader == noinstance)
					throw std::runtime_error("Failed to compile vertex shader.");

				// Build our fragment shader's source code.
				fragmentShader = buildProgram(fShaderSource, GL_FRAGMENT_SHADER, log_out, log_maxLength);

				if (fragmentShader == noinstance)
					throw std::runtime_error("Failed to compile fragment shader.");

				// Attach our compiled shaders:
				glAttachShader(programID, vertexShader);
				glAttachShader(programID, fragmentShader);

				// Link our shaders into one program.
				glLinkProgram(programID);

				// This will represent the status of our shader-program.
				GLint programStatus = GL_TRUE;

				// Check for errors:
				glGetProgramiv(programID, GL_LINK_STATUS, &programStatus);

				if (programStatus != GL_TRUE)
				{
					if (log_out != nullptr && log_maxLength > 0)
					{
						glGetProgramInfoLog(programID, log_maxLength, nullptr, log_out);
					}

					throw std::runtime_error("Failed to link shader program.");
				}
			}
			catch (std::exception&)
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

			return !error;
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

		void shader::bind() const
		{
			glUseProgram(instance);

			return;
		}

		void shader::unbind() const
		{
			glUseProgram(noinstance);

			return;
		}
	}
}