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
				virtual bool init(const GLuint* indexData, GLsizei length, GLenum usage, bool should_unbind=true, bool useLengthInBytes=false);

				inline bool init(const std::vector<GLuint>& indexData, GLenum usage, bool should_unbind=true, bool useLengthInBytes=false)
				{
					return init(indexData.data(), indexData.size(), usage, useLengthInBytes);
				}

				void destroy() override;
		};
	}
}