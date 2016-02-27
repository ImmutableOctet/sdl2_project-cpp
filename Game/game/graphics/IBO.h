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

				// Methods:
				virtual bool init(const std::vector<std::vector<GLuint>>& indexDataArray, GLenum usage, bool destroyFirst=true);

				inline bool init(const std::vector<GLuint>& indexData, GLenum usage, bool destroyFirst=true)
				{
					auto input = std::vector<std::vector<GLuint>>(1, indexData);

					return init(input, usage, destroyFirst);
				}
		};
	}
}