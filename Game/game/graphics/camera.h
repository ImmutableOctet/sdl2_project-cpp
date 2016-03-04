#pragma once

// Includes:
#include "types.h"

// GLM:
#include <glm/glm.hpp>

// Namespaces:
namespace game
{
	namespace graphics
	{
		// Classes:
		class camera
		{
			public:
				camera(const glm::vec3& position=glm::vec3(), const glm::vec3& rotation=glm::vec3());
			protected:
				// Fields:
				glm::vec3 position;
				glm::vec3 rotation;
		};
	}
}