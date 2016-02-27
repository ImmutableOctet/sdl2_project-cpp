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

		// Destructor(s):
		vertexBufferObject::~vertexBufferObject()
		{
			// Nothing so far.
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
	}
}
