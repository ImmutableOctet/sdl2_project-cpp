#pragma once

// Includes:
#include "types.h"

#include <vector>

// Namespace(s):
namespace game
{
	namespace graphics
	{
		class texture
		{
			public:
				// Constant variable(s):
				static const textureHandle notexture = textureHandle();

				// Constructor(s):
				texture();

				// Destructor(s):
				virtual ~texture();

				// Force this type to be move-only:
				texture(texture&& t) = default;
				//texture(const texture&) = delete;

				// Operator overloads:
				texture& operator=(texture&& input);

				bool operator==(textureHandle inst) const;
				bool operator==(const std::vector<textureHandle>& insts) const;

				// Methods:
				inline const std::vector<textureHandle>& getInstances() const
				{
					return instances;
				}

				virtual bool load(const char** paths, size_t count, bool destroyFirst=true);
				
				inline bool load(const std::string& path, bool destroyFirst=true)
				{
					const char* pathCharacters = path.c_str();
					const char** input = &pathCharacters;

					return load(input, 1, destroyFirst);
				}

				virtual void destroy(bool clear=true);
			protected:
				// Fields:
				std::vector<textureHandle> instances;
		};
	}
}
