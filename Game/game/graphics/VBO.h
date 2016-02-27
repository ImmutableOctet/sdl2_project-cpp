#pragma once

// Includes:
#include "bufferobject.h"

// Namespaces:
namespace game
{
	namespace graphics
	{
		// Classes:
		class vertexBufferObject : public bufferObject<FBOHandle>
		{
			public:
				// Constructor(s):
				vertexBufferObject();

				// Destructor(s):
				virtual ~vertexBufferObject();
		};
	}
}