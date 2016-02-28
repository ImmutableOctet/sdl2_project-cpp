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
			init(std::move(vertexData), std::move(indexData));
		}

		// Destructor(s):
		vertexArrayObject::~vertexArrayObject()
		{
			destroy();
		}

		// Methods:
		void vertexArrayObject::init(vertexBufferObject&& vertexData, elementBufferObject&& elementData)
		{
			vertices = std::move(vertexData);
			elements = std::move(elementData);

			bind();

			auto VBO = resource_lock<decltype(vertexData)>(vertexData);
			auto EBO = resource_lock<decltype(elementData)>(elementData);

			unbind();

			return;
		}

		void vertexArrayObject::destroy()
		{
			return;
		}
	}
}