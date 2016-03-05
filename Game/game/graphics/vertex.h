#pragma once

// Includes:
#include "types.h"

// GLM:
#include <glm/glm.hpp>

// C STDLIB:
#include <cstddef>

// Namespace(s):
namespace game
{
	namespace graphics
	{
		// Structures:
		template <typename positionType=glm::vec3, typename normalsType=glm::vec3, typename colorsType=glm::vec4, typename texCoordsType=glm::vec2>
		struct vertex
		{
			// Typedefs:
			using position_t = positionType;
			using normals_t = normalsType;
			using colors_t = colorsType;
			using texcoords_t = texCoordsType;

			// Methods:
			inline std::size_t elementCount() const
			{
				return (position.length() + normals.length() + colors.length() + texcoords.length()); // sizeof(vertex) / sizeof(GLfloat);
			}

			// Operator overloads:
			inline operator GLfloat*() const
			{
				return (GLfloat*)&position;
			}

			// Fields:
			position_t position;
			normals_t normals;
			colors_t colors;
			texcoords_t texcoords;
		};

		// Typedefs:
		using vertex_t = vertex<>;
	}
}