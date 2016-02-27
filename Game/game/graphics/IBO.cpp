#include "IBO.h"
#include "opengl.h"
#include "uniform.h"

// Namespace(s):
namespace game
{
	namespace graphics
	{
		// Classes:

		// indexBufferObject:

		// Constructor(s):
		indexBufferObject::indexBufferObject()
		{
			// Nothing so far.
		}

		// Destructor(s):
		indexBufferObject::~indexBufferObject()
		{
			// Nothing so far.
		}

		// Methods:
		bool indexBufferObject::init(const std::vector<std::vector<GLuint>>& indexDataArray, GLenum usage, bool destroyFirst)
		{
			// Check if we should release existing handles first:
			if (destroyFirst)
			{
				destroy(true);
			}

			return rawBufferUpload<GLuint, IBOHandle>(this->instances, indexDataArray, usage, GL_ELEMENT_ARRAY_BUFFER);
		}
	}
}
