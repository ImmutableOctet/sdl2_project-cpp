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
		template <typename positionType=GLfloat, typename colorType=GLfloat, typename texCoordsType=GLfloat>
		struct vertex
		{
			// Typedefs:
			using position_t = positionType;
			using color_t = colorType;
			using texcoords_t = texCoordsType;

			// Fields:
			position_t position;
			color_t color;
			texcoords_t texcoords;
		};
	}
}