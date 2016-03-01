// Includes:
#include "opengl.h"

#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

// STL:
#include <utility>

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
			init(std::forward<vertexBufferObject>(vertexData), std::forward<elementBufferObject>(indexData));
		}

		vertexArrayObject::vertexArrayObject(vertexArrayObject&& rval)
		{
			*this = std::move(rval);
		}

		// Destructor(s):
		vertexArrayObject::~vertexArrayObject()
		{
			destroy();
		}

		// Operator overloads:
		vertexArrayObject& vertexArrayObject::operator=(vertexArrayObject&& rval)
		{
			resource::operator=(std::forward<resource>(rval));

			this->vertices = std::move(rval.vertices);
			this->elements = std::move(rval.elements);

			return *this;
		}

		// Methods:
		bool vertexArrayObject::init(const std::vector<GLfloat>& vertexData, GLenum vertUsage, const std::vector<GLuint>& elementData, GLenum elemUsage, bool should_unbind)
		{
			if (exists())
			{
				return false;
			}

			// Allocate a VAO handle.
			glGenVertexArrays(1, &instance);

			bind();

			vertices.init(vertexData, vertUsage, false);
			elements.init(elementData, elemUsage, false);

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), nullptr);
			glEnableVertexAttribArray(0);

			// Unbind the vertex-buffer, but keep the element-buffer bound.
			vertices.unbind();
			//elements.unbind();

			// Check if we were requested to unbind:
			if (should_unbind)
			{
				// Unbind this VAO.
				unbind();
			}

			return true;
		}

		bool vertexArrayObject::init(vertexBufferObject&& vertexData, elementBufferObject&& elementData, bool should_unbind)
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
			//elementData.unbind();

			// Check if we were requested to unbind:
			if (should_unbind)
			{
				// Unbind this VAO.
				unbind();
			}

			return true;
		}

		void vertexArrayObject::destroy()
		{
			if (instance != noinstance)
			{
				glDeleteVertexArrays(1, &instance);

				instance = noinstance;
			}

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