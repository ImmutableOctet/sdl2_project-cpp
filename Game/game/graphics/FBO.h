#pragma once

// Includes:
#include "resource.h"

// Namespaces:
namespace game
{
	namespace graphics
	{
		// Classes:
		class frameBufferObject : public resource<FBOHandle>
		{
			public:
				// Constructor(s):
				frameBufferObject();

				// Destructor(s):
				virtual ~frameBufferObject();
		};
	}
}