// Includes:
#include "opengl.h"
#include "uniform.h"

#include "EBO.h"

// STL:
#include <stdexcept>

// Namespace(s):
namespace game
{
	namespace graphics
	{
		// Classes:

		// elementBufferObject:

		// Constructor(s):
		elementBufferObject::elementBufferObject()
		{
			// Nothing so far.
		}

		elementBufferObject::elementBufferObject(const GLuint* indexData, GLenum usage)
		{
			if (!init(indexData, usage))
			{
				throw std::runtime_error("Failed to initialize EBO using raw data.");
			}
		}

		elementBufferObject::elementBufferObject(const std::vector<GLuint>& indexData, GLenum usage)
		{
			if (!init(indexData, usage))
			{
				throw std::runtime_error("Failed to initialize EBO using 'std::vector'.");
			}
		}

		// Destructor(s):
		elementBufferObject::~elementBufferObject()
		{
			destroy();
		}

		// Operator overloads:
		elementBufferObject& elementBufferObject::operator=(elementBufferObject&& input)
		{
			resource::operator=(input);

			return *this;
		}

		// Methods:
		bool elementBufferObject::init(const GLuint* indexData, GLsizei length, GLenum usage, bool should_unbind=true, bool useLengthInBytes=false)
		{
			return generateGLBuffer(this->instance, indexData, length, usage, GL_ELEMENT_ARRAY_BUFFER, should_unbind, useLengthInBytes);
		}

		void elementBufferObject::destroy()
		{
			destroyGLBuffer(this->instance);

			return;
		}
	}
}
