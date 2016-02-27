#pragma once

// Includes:
#include "bufferobject.h"

// Namespace(s):
namespace game
{
	namespace graphics
	{
		class texture : public bufferObject<textureHandle>
		{
			public:
				// Constructor(s):
				texture();

				// Destructor(s):
				virtual ~texture();

				// Force this type to be move-only:
				texture(texture&& t) = default;
				//texture(const texture&) = delete;

				// Operator overloads:
				texture& operator=(texture&& input);

				// Methods:
				virtual bool load(const char** paths, size_t count, bool destroyFirst=true);
				
				inline bool load(const std::string& path, bool destroyFirst=true)
				{
					const char* pathCharacters = path.c_str();
					const char** input = &pathCharacters;

					return load(input, 1, destroyFirst);
				}

				virtual void destroy(bool clear=true) override;
		};
	}
}
