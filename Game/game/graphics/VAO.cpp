// Includes:
#include "opengl.h"

#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

// Namespace(s):
namespace game
{
	namespace graphics
	{
		// Classes:

		// vertexArrayObject:

		// Constructor(s):
		vertexArrayObject::vertexArrayObject()
		{
			// Nothing so far.
		}

		vertexArrayObject::vertexArrayObject(vertexBufferObject&& vertexData, elementBufferObject&& indexData)
		{
			vertices = std::move(vertexData);
			elements = std::move(indexData);
		}

		// Destructor(s):
		vertexArrayObject::~vertexArrayObject()
		{
			destroy();
		}

		// Methods:
		void vertexArrayObject::destroy()
		{
			return;
		}
	}
}