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
				texture();
				~texture();

				// Force this type to be move-only:
				texture(texture&& t) = default;
				//texture(const texture&) = delete;

				// Operator overloads:
				texture& operator=(texture&& input);

				bool operator==(textureHandle inst) const;
				bool operator==(const std::vector<textureHandle>& insts) const;
			protected:
				// Fields:
				std::vector<textureHandle> instances;
		};
	}
}
