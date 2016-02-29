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
				void init(vertexBufferObject&& vertexData, elementBufferObject&& elementData, bool should_unbind=true);

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