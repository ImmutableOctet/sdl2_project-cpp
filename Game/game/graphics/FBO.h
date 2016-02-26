#pragma once

// Includes:
#include "types.h"

// Namespaces:
namespace game
{
	namespace graphics
	{
		// Classes:
		class frameBufferObject
		{
			public:
				// Constant variable(s):
				static const FBOHandle noinstance = FBOHandle();

				// Constructor(s):
				frameBufferObject();
				virtual ~frameBufferObject();
			protected:
				FBOHandle instance = noinstance;
		};
	}
}