#pragma once

// Includes:
#include "resource.h"

// STL:
#include <string>

// C STDLIB:
#include <cstddef>

// Namespace(s):
namespace game
{
	namespace graphics
	{
		class texture : public resource<textureHandle>
		{
			public:
				// Constructor(s):
				texture();

				// Destructor(s):
				~texture(); // virtual

				// Force this type to be move-only:
				texture(texture&& t) = default;
				//texture(const texture&) = delete;

				// Operator overloads:
				texture& operator=(texture&& input);

				// Methods:
				virtual bool load(const char* path, bool should_unbind=true);
				
				inline bool load(const std::string& path, bool should_unbind=true)
				{
					return load(path.c_str(), should_unbind);
				}

				void destroy() override;

				void bind() const override;
				void unbind() const override;
		};
	}
}
