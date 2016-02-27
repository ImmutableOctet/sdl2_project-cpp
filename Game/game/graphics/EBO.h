#pragma once

// Includes:
#include "resource.h"

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
				indexBufferObject(const std::vector<GLuint>& indexData, GLenum usage);

				// Force this type to be move-only:
				indexBufferObject(indexBufferObject&& t) = default;
				//indexBufferObject(const indexBufferObject&) = delete;

				// Destructor(s):
				virtual ~indexBufferObject();

				// Operator overloads:
				indexBufferObject& operator=(indexBufferObject&& input);

				// Methods:
				virtual bool init(const std::vector<std::vector<GLuint>>& indexDataArray, GLenum usage, bool destroyFirst=true);

				inline bool init(const std::vector<GLuint>& indexData, GLenum usage, bool destroyFirst=true)
				{
					auto input = std::vector<std::vector<GLuint>>(1, indexData);

					return init(input, usage, destroyFirst);
				}

				virtual void destroy(bool clear=true) override;
		};
	}
}