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
		template <typename position_t, typename color_t, typename texcoords_t>
		struct vertex
		{
			// Fields:
			position_t position;
			color_t color;
			texcoords_t texcoords;
		};
	}
}