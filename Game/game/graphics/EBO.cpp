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
		bool elementBufferObject::init(const GLuint* indexDataArray, GLenum usage)
		{
			return rawBufferUpload<GLuint, IBOHandle>(this->instance, indexDataArray, usage, GL_ELEMENT_ARRAY_BUFFER);
		}

		void elementBufferObject::destroy()
		{
			destroyGLBuffer(this->instance);

			return;
		}
	}
}
