// Includes:

// Local:
#include "opengl.h"
#include "texture.h"
#include "uniform.h"

// SDL:
#include <SDL.h>
#include <SDL_image.h>

// STL:
#include <utility>
#include <stdexcept>
#include <string>

// C STDLIB:
#include <cstddef>

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
			destroy();
		}

		// Operator overloads:
		texture& texture::operator=(texture&& input)
		{
			resource::operator=(input);

			return *this;
		}

		// Methods:
		bool texture::load(const char* path, bool should_unbind)
		{
			try
			{
				// Generate texture handles.
				glGenTextures(1, &instance);

				// Load a surface using the described file-path.
				SDL_Surface* surface = IMG_Load(path);

				// Bind the texture-handle we generated.
				bind();

				// Upload the surface's contents to the GPU.
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGB, GL_UNSIGNED_BYTE, surface->pixels); // 4
				
				// Release the surface we loaded.
				SDL_FreeSurface(surface);

				// Not sure about these yet:
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

				if (should_unbind)
				{
					unbind();
				}
			}
			catch (const std::exception&)
			{
				
				destroy();

				// Tell the user the bad news.
				return false;
			}

			// Return the default response. (Success)
			return true;
		}

		void texture::destroy()
		{
			if (instance != noinstance)
			{
				glDeleteTextures(1, &instance);
				instance = noinstance;
			}

			return;
		}

		void texture::bind() const
		{
			glBindTexture(GL_TEXTURE_2D, instance);

			return;
		}

		void texture::unbind() const
		{
			glBindTexture(GL_TEXTURE_2D, noinstance);
		}
	}
}