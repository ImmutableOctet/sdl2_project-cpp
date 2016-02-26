#pragma once

// Includes:
#include "types.h"

// Namespace(s):
namespace game
{
	namespace graphics
	{
		class texture
		{
			public:
				texture();
				~texture();
			protected:
				textureHandle instance;
		};
	}
}
