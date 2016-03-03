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
				static const GLsizei COLOR_DATA_EXT_SIZE = 1;

				static const GLuint VERTEX_DATA_INDEX = 0;
				static const GLuint COLOR_DATA_INDEX = 1;

				static const GLsizei VERTEX_DATA_LENGTH = 3; // 4;
				static const GLsizei COLOR_DATA_BASE_LENGTH = 3;
				static const GLsizei COLOR_DATA_EXT_LENGTH = (COLOR_DATA_BASE_LENGTH + COLOR_DATA_EXT_SIZE);

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

				/*
					These methods describe the contents of 'vertices', which
					needs to be initialized and bound before calling these.
					
					To simplify the process, call the bare version of 'init' for this
					object, then regular 'init' versions for the others.

					The result should be a bound VBO and EBO, with the VBO later needing to be unbound.
					Such behavior must be done with knowledge of "unbind" toggles when initializing.
					If not noted, you will need to call 'bind' manually.
					
					Regardless of usage patterns, 'unbind' should always be called on the VBO before setup is finished.
					Unbinding does not apply to EBOs for several reasons.

					For a much simpler experience, use the fully featured overload of 'init' found in this class.
				*/

				template <typename vertexType=GLfloat, typename colorType=vertexType>
				inline void describeVertexData(bool color_enabled, bool color_alpha_enabled=false, bool normalized=false, GLuint index=VERTEX_DATA_INDEX) // GL_FALSE
				{
					GLsizei stride = (VERTEX_DATA_LENGTH * sizeof(vertexType));
					GLsizei colors = 0;

					if (color_enabled)
					{
						colors += COLOR_DATA_BASE_LENGTH;

						if (color_alpha_enabled)
						{
							colors += COLOR_DATA_EXT_SIZE;
						}
					}

					stride += (colors * sizeof(colorType));

					glVertexAttribPointer(index, VERTEX_DATA_LENGTH, getGLType<vertexType>(), normalized, stride, reinterpret_cast<GLvoid*>(0));
					glEnableVertexAttribArray(index);

					return;
				}

				template <typename colorType=GLfloat, typename vertexType=colorType>
				inline void describeColorData(bool alpha_enabled, bool normalized=false, GLuint index=COLOR_DATA_INDEX)
				{
					// Resolve the number of color channels we're working with.
					GLsizei colors = ((!alpha_enabled) ? COLOR_DATA_BASE_LENGTH : COLOR_DATA_EXT_LENGTH);

					GLsizei stride = (colors * sizeof(colorType));

					GLsizei vertices = VERTEX_DATA_LENGTH;
					GLsizei vertexStride = (vertices * sizeof(vertexType));

					stride += vertexStride;

					glVertexAttribPointer(index, colors, getGLType<colorType>(), normalized, stride, reinterpret_cast<const GLvoid*>(vertexStride));
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

				template <typename VBOContentType=GLfloat>
				inline bool init(const std::vector<VBOContentType>& vertexData, GLenum vertUsage, const std::vector<GLuint>& elementData, GLenum elemUsage, bool vertexColor=false, bool vertexColor_alpha=false, bool should_unbind=true)
				{
					if (contentsExist())
					{
						return false;
					}

					init(false);

					vertices.init(vertexData, vertUsage, false);
					elements.init(elementData, elemUsage, false);

					describeVertexData<VBOContentType, VBOContentType>(vertexColor, vertexColor_alpha);

					if (vertexColor)
					{
						describeColorData<VBOContentType, VBOContentType>(vertexColor_alpha);
					}

					// Unbind the vertex-buffer, but keep the element-buffer bound.
					vertices.unbind(); // elements.unbind();

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

				void draw(GLenum mode=GL_TRIANGLES);
			protected:
				// Fields:
				vertexBufferObject vertices;
				elementBufferObject elements;
		};
	}
}