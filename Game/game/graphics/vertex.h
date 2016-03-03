#pragma once

// Includes:
#include "types.h"

//#include <glm/glm.hpp>

// Namespace(s):
namespace game
{
	namespace graphics
	{
		// Structures:
		template <typename position_t, typename color_t, typename texcoord_t>
		struct vertex
		{
			// Fields:
			position_t x, y, z; // w;
			color_t r, g, b; // a;
			texcoord_t u, v;
		};
	}
}