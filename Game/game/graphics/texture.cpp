// Includes:

// Local:
#include "texture.h"
#include "opengl.h"

// SDL:
#include <SDL.h>
#include <SDL_image.h>

// STL:
#include <utility>

// Namespace(s):
namespace game
{
	namespace graphics
	{
		// Classes:

		// texture:

		// Constructor(s):
		texture::texture()
		{
			// Nothing so far.
		}

		// Destructor(s):
		texture::~texture()
		{
			if (!instances.empty())
			{
				glDeleteTextures(static_cast<GLsizei>(instances.size()), instances.data());
			}
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

		// Methods:
		void texture::load(const std::string& path)
		{
			SDL_Surface* surface = IMG_Load(path.c_str());



			return;
		}
	}
}