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
			public:
				// Constructor(s):
				vertexArrayObject();
				vertexArrayObject(vertexBufferObject&& vertexData, elementBufferObject&& elementData);

				vertexArrayObject(vertexArrayObject&&) = default;
				//vertexArrayObject(const vertexArrayObject&) = delete;

				// Destructor(s):
				~vertexArrayObject();

				// Methods:
				void destroy() override;

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