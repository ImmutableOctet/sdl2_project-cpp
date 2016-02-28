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
			protected:
				vertexBufferObject vertices;
				elementBufferObject indices;
		};
	}
}