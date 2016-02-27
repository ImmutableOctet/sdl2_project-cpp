#pragma once

// Includes:
#include "bufferobject.h"

// Namespaces:
namespace game
{
	namespace graphics
	{
		// Classes:
		class vertexBufferObject : public bufferObject<FBOHandle>
		{
			public:
				// Constructor(s):
				vertexBufferObject();

				// Destructor(s):
				virtual ~vertexBufferObject();

				// Methods:
				virtual bool init(const std::vector<std::vector<GLfloat>>& vertexDataArray, GLenum usage, bool destroyFirst=true);

				inline bool init(const std::vector<GLfloat>& vertexData, GLenum usage, bool destroyFirst=true)
				{
					auto input = std::vector<std::vector<GLfloat>>(1, vertexData);

					return init(input, usage, destroyFirst);
				}
		};
	}
}