#pragma once

// Includes:
#include "resource.h"

// Namespaces:
namespace game
{
	namespace graphics
	{
		// Classes:
		class elementBufferObject : public bufferObject<IBOHandle>
		{
			public:
				// Constructor(s):
				elementBufferObject();
				elementBufferObject(const std::vector<GLuint>& indexData, GLenum usage);

				// Force this type to be move-only:
				elementBufferObject(elementBufferObject&& t) = default;
				//elementBufferObject(const elementBufferObject&) = delete;

				// Destructor(s):
				virtual ~elementBufferObject();

				// Operator overloads:
				elementBufferObject& operator=(elementBufferObject&& input);

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