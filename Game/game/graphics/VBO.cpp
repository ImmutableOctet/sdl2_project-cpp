#include "VBO.h"
#include "opengl.h"
#include "uniform.h"

// Namespace(s):
namespace game
{
	namespace graphics
	{
		// Classes:

		// vertexBufferObject:

		// Constructor(s):
		vertexBufferObject::vertexBufferObject()
		{
			// Nothing so far.
		}

		vertexBufferObject::vertexBufferObject(const std::vector<GLfloat>& vertexData, GLenum usage)
		{
			init(vertexData, usage, false);
		}

		// Destructor(s):
		vertexBufferObject::~vertexBufferObject()
		{
			// Nothing so far.
		}

		// Operator overloads:
		vertexBufferObject& vertexBufferObject::operator=(vertexBufferObject&& input)
		{
			destroy(true);

			std::swap(this->instances, input.instances);

			return *this;
		}

		// Methods:
		bool vertexBufferObject::init(const std::vector<std::vector<GLfloat>>& vertexDataArray, GLenum usage, bool destroyFirst)
		{
			// Check if we should release existing handles first:
			if (destroyFirst)
			{
				destroy(true);
			}

			return rawBufferUpload<GLfloat, IBOHandle>(this->instances, vertexDataArray, usage, GL_ARRAY_BUFFER);
		}

		void vertexBufferObject::destroy(bool clear)
		{
			destroyBuffers(this->instances, clear);

			return;
		}
	}
}
