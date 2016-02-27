#pragma once

// Includes:
#include "bufferobject.h"

#include "VBO.h"
#include "IBO.h"

// Namespace(s):
namespace game
{
	namespace graphics
	{
		// Structures:

		// This is used to represent a group vertices and indices.
		struct vertexDataManifold
		{
			VAOHandle instance;

			vertexBufferObject vertices;
			indexBufferObject indices;
		};

		// Classes:
		class vertexArrayObject : public bufferObject<vertexDataManifold>
		{

		};
	}
}