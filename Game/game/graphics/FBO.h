#pragma once

// Includes:
#include "bufferobject.h"

// Namespaces:
namespace game
{
	namespace graphics
	{
		// Classes:
		class frameBufferObject : public bufferObject<FBOHandle>
		{
			public:
				// Constructor(s):
				frameBufferObject();

				// Destructor(s):
				virtual ~frameBufferObject();
		};
	}
}