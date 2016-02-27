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
					// Retrieve the current surface's path.
					const char* path = paths[currentIndex];

					// Load a surface using the described file-path.
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

					// Retrive the current texture-handle.
					auto currentHandle = raw_ptr[currentIndex];

					// Bind the texture-handle we generated.
					glBindTexture(GL_TEXTURE_2D, currentHandle);

					// Upload the surface's contents to the GPU.
					glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGB, GL_UNSIGNED_BYTE, surface->pixels); // 4

					// Release the surface we loaded.
					SDL_FreeSurface(surface);

					// Not sure about these yet:
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				}
			}
			catch (const std::exception&)
			{
				// Error recovery:
				if (currentIndex > 0 && currentIndex != noindex)
				{
					// Release our texture-handles to the driver.
					glDeleteTextures(currentIndex, raw_ptr);
				}

				// Resize back to what the vector was.
				instances.resize(startIndex);

				// Tell the user the bad news.
				return false;
			}

			// Return the default response. (Success)
			return true;
		}

		void texture::destroy(bool clear)
		{
			// Check if we have any textures bound to this object:
			if (!instances.empty())
			{
				// Release our texture-handles to the driver.
				glDeleteTextures(static_cast<GLsizei>(instances.size()), instances.data());

				// Check if the user requested a full clear of 'instances'.
				if (clear)
				{
					// Clear the internal 'textureHandle' container.
					instances.clear();
				}
			}

			return;
		}
	}
}