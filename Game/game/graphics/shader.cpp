// Includes:
#include "config.h"

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

		void shader::bindProgram(shaderHandle instance)
		{
			glUseProgram(instance);

			return;
		}

		void shader::unbindProgram()
		{
			glUseProgram(noinstance);

			return;
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
			bindProgram(instance);

			return;
		}

		void shader::unbind() const
		{
			unbindProgram();

			return;
		}

		// shader_lock:

		// Methods:
		void shader_lock::bind(shaderHandle prev_inst) // resourceHandle_t
		{
			prevHandle = prev_inst;

			super::bind();

			return;
		}

		void shader_lock::bind(bool nested)
		{
			if (nested)
			{
				bool result = true;
				GLint value;

				glGetIntegerv(GL_LIST_INDEX, &value);

				if (value != 0)
				{
					glGetIntegerv(GL_LIST_MODE, &value);

					result = (value == GL_COMPILE);
				}
				else
				{
					result = false;
				}

				if (!result)
				{
					throw std::runtime_error("Invalid environment to perform a nested shader-lock.");
				}

				// Retrieve the current shader handle.
				glGetIntegerv(GL_CURRENT_PROGRAM, &value);

				if (value != shader::noinstance) // resourceType_t::noinstance
				{
					bind(static_cast<shaderHandle>(value)); // resourceHandle_t

					return;
				}
			}

			super::bind();
			
			return;
		}

		void shader_lock::unbind(bool resolveNesting)
		{
			super::unbind();

			if (resolveNesting)
			{
				if (prevHandle != shader::noinstance) // resourceType_t::noinstance
				{
					shader::bindProgram(prevHandle);

					prevHandle = shader::noinstance; // resourceType_t::noinstance
				}
			}

			return;
		}

		void shader_lock::bind()
		{
			#ifdef SHADER_LOCK_SAFE
				bind(true);
			#else
				bind(false);
			#endif

			return;
		}

		void shader_lock::unbind()
		{
			//#ifdef SHADER_LOCK_SAFE
			unbind(true);
			//#endif

			return;
		}
	}
}