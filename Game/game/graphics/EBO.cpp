// Includes:
#include "opengl.h"
#include "uniform.h"

#include "EBO.h"

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

		elementBufferObject::elementBufferObject(const std::vector<GLuint>& indexData, GLenum usage)
		{
			init(indexData, usage, false);
		}

		// Destructor(s):
		elementBufferObject::~elementBufferObject()
		{
			// Nothing so far.
		}

		// Operator overloads:
		elementBufferObject& elementBufferObject::operator=(elementBufferObject&& input)
		{
			resource::operator=(input);

			return *this;
		}

		// Methods:
		bool elementBufferObject::init(const std::vector<std::vector<GLuint>>& indexDataArray, GLenum usage, bool destroyFirst)
		{
			// Check if we should release existing handles first:
			if (destroyFirst)
			{
				destroy(true);
			}

			return rawBufferUpload<GLuint, IBOHandle>(this->instances, indexDataArray, usage, GL_ELEMENT_ARRAY_BUFFER);
		}

		void elementBufferObject::destroy(bool clear)
		{
			destroyBuffers(this->instances, clear);

			return;
		}
	}
}
