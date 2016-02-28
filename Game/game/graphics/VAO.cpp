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

		// Operator overloads:
		vertexArrayObject& vertexArrayObject::operator=(vertexArrayObject&& input)
		{
			resource::operator=(input);

			return *this;
		}

		// Methods:
		void vertexArrayObject::init(vertexBufferObject&& vertexData, elementBufferObject&& elementData, bool should_unbind)
		{
			// Take ownership of 'vertexData' and 'elementData':
			vertices = std::move(vertexData);
			elements = std::move(elementData);

			// Allocate a VAO handle.
			glGenVertexArrays(1, &instance);

			bind();

			vertexData.bind();
			elementData.bind();

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), nullptr);
			glEnableVertexAttribArray(0);

			// Unbind the vertex-buffer, but keep the element-buffer bound.
			vertexData.unbind();

			// Check if we were requested to unbind:
			if (should_unbind)
			{
				// Unbind this VAO.
				unbind();
			}

			return;
		}

		void vertexArrayObject::destroy()
		{
			glDeleteVertexArrays(1, &instance);
			
			instance = noinstance;

			return;
		}

		void vertexArrayObject::bind() const
		{
			glBindVertexArray(instance);

			return;
		}

		void vertexArrayObject::unbind() const
		{
			glBindVertexArray(noinstance);

			return;
		}
	}
}