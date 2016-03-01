#pragma once

// Includes:
#include "resource.h"

#include "VBO.h"
#include "EBO.h"

#include "uniform.h"

// Namespace(s):
namespace game
{
	namespace graphics
	{
		// Classes:
		class vertexArrayObject : public resource<VAOHandle>
		{
			private:
				// Typedefs:
				using super = resource<VAOHandle>;
			public:
				// Constant variable(s):
				static const GLuint VERTEX_DATA_INDEX = 0;

				// Constructor(s):
				vertexArrayObject();

				// Force this type to be move-only:
				vertexArrayObject(const vertexArrayObject&) = delete;
				vertexArrayObject(vertexArrayObject&& rval);

				// Destructor(s):
				~vertexArrayObject();

				// Operator overloads:
				vertexArrayObject& operator=(vertexArrayObject&&);

				// Methods:

				// This method describes the contents of 'vertices'.
				template <typename vertexType = GLfloat>
				inline void describeVertexData(bool normalized = false, GLuint index = VERTEX_DATA_INDEX, GLsizei vertexPositionSize = 3) // GL_FALSE
				{
					glVertexAttribPointer(index, vertexPositionSize, getGLType<vertexType>(), normalized, vertexPositionSize * sizeof(vertexType), nullptr);
					glEnableVertexAttribArray(index);

					return;
				}

				/*
					This performs the initial setup for binding data to this object.
					A call to this overload should be followed by a call to one of the others.
					
					In addition, manually setting up this VAO is accepted
					when done correctly, but this is not recommended.

					Alternatively, a call to 'destroy' will suffice. (If destroying the object)
				*/

				bool init(bool should_unbind=true);

				template <typename vertexType=GLfloat>
				inline bool init(const std::vector<vertexType>& vertexData, GLenum vertUsage, const std::vector<GLuint>& elementData, GLenum elemUsage, GLuint vertexPositionSize=3, bool should_unbind=true)
				{
					if (contentsExist())
					{
						return false;
					}

					init(false);

					vertices.init(vertexData, vertUsage, false);
					elements.init(elementData, elemUsage, false);

					describeVertexData<vertexType>();

					// Unbind the vertex-buffer, but keep the element-buffer bound.
					vertices.unbind(); //elements.unbind();

					// Check if we were requested to unbind:
					if (should_unbind)
					{
						// Unbind this VAO.
						unbind();
					}

					return true;
				}

				void destroy() override;

				void bind() const override;
				void unbind() const override;

				inline const vertexBufferObject& getVertices() const
				{
					return vertices;
				}

				inline const elementBufferObject& getElements() const
				{
					return elements;
				}

				// This returns 'true' if 'vertices' and 'elements' both exist.
				inline bool contentsExist() const
				{
					return (vertices.exists() && elements.exists());
				}

				// This returns 'true' if either 'vertices' or 'elements' exists.
				inline bool hasContent() const
				{
					return (vertices.exists() || elements.exists());
				}

				bool setVertices(vertexBufferObject&& input);
				bool setElements(elementBufferObject&& input);
			protected:
				vertexBufferObject vertices;
				elementBufferObject elements;
		};
	}
}