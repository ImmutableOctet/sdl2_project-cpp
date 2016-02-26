// Includes:
#include "texture.h"
#include "opengl.h"

#include <utility>

// Namespace(s):
namespace game
{
	namespace graphics
	{
		// Classes:

		// texture:
		texture::texture()
		{
			// Nothing so far.
		}

		texture::~texture()
		{
			glDeleteTextures(instances.size(), instances.data());
		}

		// Operator overloads:
		texture& texture::operator=(texture&& input)
		{
			this->instances = std::move(input.instances);

			return *this;
		}

		bool texture::operator==(textureHandle inst) const
		{
			for (const auto& handle : instances)
			{
				if (handle == inst)
				{
					return true;
				}
			}

			// Return the default response.
			return false;
		}

		bool texture::operator==(const std::vector<textureHandle>& insts) const
		{
			return (insts == instances);
		}
	}
}