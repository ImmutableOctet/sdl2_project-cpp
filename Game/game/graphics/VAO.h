#pragma once

// Includes:
#include "resource_container.h"

#include "VBO.h"
#include "EBO.h"

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
			elementBufferObject indices;
		};

		// Classes:
		class vertexArrayObject : public resourceContainer<vertexDataManifold>
		{
			// Nothing so far.
		};
	}
}