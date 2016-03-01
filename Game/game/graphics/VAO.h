#pragma once

// Includes:
#include "resource.h"

#include "VBO.h"
#include "EBO.h"

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
				// Constructor(s):
				vertexArrayObject();
				vertexArrayObject(vertexBufferObject&& vertexData, elementBufferObject&& elementData);

				// Force this type to be move-only:
				vertexArrayObject(const vertexArrayObject&) = delete;
				vertexArrayObject(vertexArrayObject&& rval);

				// Destructor(s):
				~vertexArrayObject();

				// Operator overloads:
				vertexArrayObject& operator=(vertexArrayObject&&);

				// Methods:

				// This performs the initial setup for binding data to this object.
				// A call to this overload should be followed by a call to one of the others.
				// Alternatively, a call to 'destroy' will suffice.
				bool init(bool should_unbind=false);

				bool init(const std::vector<GLfloat>& vertexData, GLenum vertUsage, const std::vector<GLuint>& elementData, GLenum elemUsage, bool should_unbind=true);
				bool init(vertexBufferObject&& vertexData, elementBufferObject&& elementData, bool should_unbind=true);

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
			protected:
				vertexBufferObject vertices;
				elementBufferObject elements;
		};
	}
}