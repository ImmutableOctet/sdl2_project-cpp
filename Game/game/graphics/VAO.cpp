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
		bool vertexArrayObject::init(bool should_unbind)
		{
			// Check if we've already executed this method:
			if (exists())
			{
				return false;
			}

			// Allocate a VAO handle.
			glGenVertexArrays(1, &instance);

			if (!should_unbind)
			{
				bind(); // unbind();
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

		bool vertexArrayObject::setVertices(vertexBufferObject && input)
		{
			if (vertices.exists())
			{
				return false;
			}

			vertices = std::move(input);

			return true;
		}

		bool vertexArrayObject::setElements(elementBufferObject&& input)
		{
			if (elements.exists())
			{
				return false;
			}

			elements = std::move(input);

			return true;
		}

		void vertexArrayObject::draw(GLenum mode) // const
		{
			bind();

			if (elements.exists())
			{
				glDrawElements(mode, static_cast<GLsizei>(elements.size()), getGLType<elementBufferObject::type>(), nullptr);
			}
			else
			{
				glDrawElements(mode, static_cast<GLsizei>(vertices.size()), getGLType<vertexBufferObject::type>(), nullptr);
			}

			unbind();

			return;
		}
	}
}