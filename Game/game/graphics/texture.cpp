// Includes:

// Local:
#include "texture.h"
#include "opengl.h"

// SDL:
#include <SDL.h>
#include <SDL_image.h>

// STL:
#include <utility>
#include <stdexcept>
#include <string>

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
			destroy(false);
		}

		// Operator overloads:
		texture& texture::operator=(texture&& input)
		{
			destroy(true);

			std::swap(this->instances, input.instances);

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
		bool texture::load(const char** paths, size_t count, bool destroyFirst)
		{
			// Typedefs:
			typedef size_t iterationType; // int

			// Constant variable(s):

			// This is used to represent an undefined index.
			static const iterationType noindex = static_cast<iterationType>(-1);

			// Check if we should destroy existing textures first:
			if (destroyFirst)
			{
				destroy(true);
			}

			// Get the current size, so we can use it as a starting index.
			auto startIndex = instances.size();

			// Allocate the extra memory we need.
			instances.resize(startIndex + count, noinstance);
			
			// Point to the new area.
			textureHandle* const raw_ptr = (instances.data() + startIndex);

			// This represents the active array-index when loading textures.
			iterationType currentIndex = noindex;

			try
			{
				// Generate texture handles.
				glGenTextures(static_cast<GLsizei>(count), raw_ptr);

				for (currentIndex = 0; currentIndex < count; currentIndex++)
				{
					const char* path = paths[currentIndex];
					SDL_Surface* surface = IMG_Load(path);

					/*
						try
						{
							// ...
						}
						catch (const std::exception& e)
						{
							if (surface != nullptr)
							{
								SDL_FreeSurface(surface);
							}

							throw e;
						}
						if (surface == nullptr)
						{
							throw std::runtime_error("Unable to surface at \q" + std::string(path) + "\q");
						}
					*/

					auto currentHandle = raw_ptr[currentIndex];

					glBindTexture(GL_TEXTURE_2D, currentHandle);
					glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGB, GL_UNSIGNED_BYTE, surface->pixels); // 4

					SDL_FreeSurface(surface);

					// Not sure about these yet:
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				}
			}
			catch (const std::exception&)
			{
				if (currentIndex > 0 && currentIndex != noindex)
				{
					glDeleteTextures(currentIndex, raw_ptr);
				}

				// Resize back to what the vector was.
				instances.resize(startIndex);

				return false;
			}

			// Return the default response.
			return true;
		}

		void texture::destroy(bool clear)
		{
			if (!instances.empty())
			{
				glDeleteTextures(static_cast<GLsizei>(instances.size()), instances.data());

				if (clear)
				{
					instances.clear();
				}
			}

			return;
		}
	}
}