#pragma once

// Includes:
#include "resource.h"

// Namespaces:
namespace game
{
	namespace graphics
	{
		// Classes:
		class elementBufferObject : public resource<IBOHandle>
		{
			public:
				// Constructor(s):
				elementBufferObject();
				elementBufferObject(const GLuint* indexData, GLenum usage);
				elementBufferObject(const std::vector<GLuint>& indexData, GLenum usage);

				// Force this type to be move-only:
				elementBufferObject(elementBufferObject&& t) = default;
				//elementBufferObject(const elementBufferObject&) = delete;

				// Destructor(s):
				~elementBufferObject(); // virtual

				// Operator overloads:
				elementBufferObject& operator=(elementBufferObject&& input);

				// Methods:
				virtual bool init(const GLuint* indexDataArray, GLenum usage);

				inline bool init(const std::vector<GLuint>& indexData, GLenum usage)
				{
					return init(indexData.data(), usage);
				}

				void destroy() override;
		};
	}
}