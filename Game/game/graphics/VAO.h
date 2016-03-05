#pragma once

// Includes:
#include "resource.h"

#include "VBO.h"
#include "EBO.h"

#include "uniform.h"

// STL:
#include <type_traits>

// C STDLIB:
#include <cstddef>

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
				static const GLuint TEXTURE_DATA_INDEX = 2;

				static const GLsizei VERTEX_DATA_LENGTH = 3; // 4;
				static const GLsizei COLOR_DATA_BASE_LENGTH = 3;
				static const GLsizei COLOR_DATA_EXT_LENGTH = (COLOR_DATA_BASE_LENGTH + COLOR_DATA_EXT_SIZE);
				static const GLsizei TEXTURE_DATA_LENGTH = 2;

				// Structures:
				struct vertexData_descriptor
				{
					// Fields:
					bool color;
					bool color_alpha;
					bool texture_coords;
				};

				struct vertexData_strideInfo
				{
					// Fields:
					GLsizei vertexStride;
					GLsizei colorStride;
					GLsizei textureStride;

					// Operator overloads:

					// This is used to retrieve the virtual address mapped to 'index'.
					inline const GLvoid* operator[](std::size_t index) const
					{
						GLbyte* v_output = 0;

						if (index > VERTEX_DATA_INDEX)
						{
							v_output += vertexStride;

							if (index > COLOR_DATA_INDEX)
							{
								v_output += colorStride;

								if (index > TEXTURE_DATA_INDEX)
								{
									v_output += textureStride;
								}
							}
						}

						return reinterpret_cast<const GLvoid*>(v_output);
					}
				};

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

				// Intermediate routines:
				template <typename vertexType = GLfloat, typename colorType = vertexType, typename texCoordType = vertexType>
				inline GLsizei describe_calculateStride(GLsizei vertex, GLsizei colors, GLsizei textureCoords, vertexData_strideInfo* opt_out=nullptr) const
				{
					GLsizei vertexStride = (vertex * sizeof(vertexType));
					GLsizei colorStride = (colors * sizeof(colorType));
					GLsizei textureStride = (textureCoords * sizeof(texCoordType));

					if (opt_out != nullptr)
					{
						*opt_out = {};
						opt_out->vertexStride = vertexStride;
						opt_out->colorStride = colorStride;
						opt_out->textureStride = textureStride;
					}

					return (vertexStride + colorStride + textureStride);
				}

				inline GLsizei describe_getColorCount(bool color_enabled, bool color_alpha_enabled) const
				{
					GLsizei colors = 0;

					if (color_enabled)
					{
						colors += COLOR_DATA_BASE_LENGTH;

						if (color_alpha_enabled)
						{
							colors += COLOR_DATA_EXT_SIZE; // colors = COLOR_DATA_EXT_LENGTH;
						}
					}

					return colors;
				}

				template <typename vertexType = GLfloat, typename colorType = vertexType, typename texCoordType = vertexType>
				inline GLsizei describe_calculateStride(const vertexData_descriptor& config, vertexData_strideInfo* opt_out=nullptr) const
				{
					return describe_calculateStride<vertexType, colorType, texCoordType>(VERTEX_DATA_LENGTH, describe_getColorCount(config.color, config.color_alpha), (config.texture_coords) ? TEXTURE_DATA_LENGTH : 0, opt_out);
				}

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

				template <typename vertexType=GLfloat>
				inline void describeVertexPosition(GLsizei stride, bool normalized=false, GLuint index=VERTEX_DATA_INDEX, const GLvoid* __v_firstElement=0) const // GL_FALSE
				{
					glVertexAttribPointer(index, VERTEX_DATA_LENGTH, getGLType<vertexType>(), normalized, stride, __v_firstElement);
					glEnableVertexAttribArray(index);

					return;
				}

				template <typename colorType=GLfloat>
				inline void describeVertexColor(GLsizei stride, const GLvoid* v_firstElement, bool alpha_enabled, bool normalized=false, GLuint index=COLOR_DATA_INDEX) const
				{
					glVertexAttribPointer(index, describe_getColorCount(true, alpha_enabled), getGLType<colorType>(), normalized, stride, v_firstElement);
					glEnableVertexAttribArray(index);

					return;
				}

				template <typename texCoordType=GLfloat>
				inline void describeVertexTextureCoords(GLsizei stride, const GLvoid* v_firstElement, bool normalized=false, GLuint index=TEXTURE_DATA_INDEX) const
				{
					glVertexAttribPointer(index, TEXTURE_DATA_LENGTH, getGLType<texCoordType>(), normalized, stride, v_firstElement);
					glEnableVertexAttribArray(index);

					return;
				}

				// This executes the other description-commands.
				template <typename VBOContentType = GLfloat>
				inline bool describeVertexData(bool vertexColor, bool vertexColor_alpha, bool texCoords) const
				{
					// Describe the contents of 'vertices' to this VAO:

					// Load our configuration from the passed parameters. (Interface may be changed later)
					const vertexData_descriptor config = { vertexColor, vertexColor_alpha, texCoords };

					// Allocate a default initialized/uninitialized stride-information block.
					vertexData_strideInfo strideInfo;

					// Calculate the stride of our vertex entries, copying data into 'strideInfo' for later use.
					auto stride = describe_calculateStride<VBOContentType, VBOContentType, VBOContentType>(config, &strideInfo);

					// Describe the vertex positions.
					describeVertexPosition<VBOContentType>(stride);

					if (vertexColor)
					{
						// Describe the color data.
						describeVertexColor<VBOContentType>(stride, strideInfo[COLOR_DATA_INDEX], vertexColor_alpha);
					}

					if (texCoords)
					{
						// Describe the texture-coordinates.
						describeVertexTextureCoords<VBOContentType>(stride, strideInfo[TEXTURE_DATA_INDEX]);
					}

					// Return the default response.
					return true;
				}

				/*
					This performs the initial setup for binding data to this object.
					A call to this overload should be followed by a call to one of the others.
					
					In addition, manually setting up this VAO is accepted
					when done correctly, but this is not recommended.

					Alternatively, a call to 'destroy' will suffice. (If destroying the object)
				*/

				bool init(bool should_unbind=true);

				template <typename vertContainer, typename elemContainer, typename VBOContentType=GLfloat, typename EBOContentType=GLuint>
				inline bool init(const vertContainer& vertexData, std::size_t vertexCount, GLenum vertUsage, const elemContainer& elementData, GLenum elemUsage, bool vertexColor, bool vertexColor_alpha, bool texCoords, bool should_unbind=true)
				{
					if (contentsExist())
					{
						return false;
					}

					// Perform the initial setup process.
					init(false);

					// Initialize our vertex-data and element-data (Indices):
					vertices.init(vertexData, vertexCount, vertUsage, false);
					elements.init(elementData, elemUsage, false);

					// Describe the vertex-data we uploaded via 'vertices'.
					describeVertexData<VBOContentType>(vertexColor, vertexColor_alpha, texCoords);

					// Unbind the vertex-buffer, but keep the element-buffer bound.
					vertices.unbind(); // elements.unbind();

					// Check if the user wants us to unbind:
					if (should_unbind)
					{
						// Unbind this VAO.
						unbind();
					}

					// Return the default response.
					return true;
				}

				template <typename vertContainer, typename VBOContentType=GLfloat>
				inline bool init(const vertContainer& vertexData, std::size_t vertexCount, GLenum vertUsage, bool vertexColor, bool vertexColor_alpha, bool texCoords, bool should_unbind=true)
				{
					if (contentsExist())
					{
						return false;
					}

					// Perform the initial setup process.
					init(false);

					// Initialize/upload our vertex-data:
					vertices.init(vertexData, vertexCount, vertUsage, false);

					// Describe the vertex-data we uploaded via 'vertices'.
					describeVertexData<VBOContentType>(vertexColor, vertexColor_alpha, texCoords);

					// Unbind the vertex-buffer.
					vertices.unbind();

					// Check if the user wants us to unbind:
					if (should_unbind)
					{
						// Unbind this VAO.
						unbind();
					}

					// Return the default response.
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

				// Fields:
				vertexBufferObject vertices;
				elementBufferObject elements;
		};
	}
}