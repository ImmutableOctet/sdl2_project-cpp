#pragma once

// Includes:
#include "bufferobject.h"

// Namespaces:
namespace game
{
	namespace graphics
	{
		// Classes:
		class indexBufferObject : public bufferObject<IBOHandle>
		{
			public:
				// Constructor(s):
				indexBufferObject();

				// Destructor(s):
				virtual ~indexBufferObject();
		};
	}
}