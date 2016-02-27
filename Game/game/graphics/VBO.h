#pragma once

// Includes:
#include "resource.h"

// Namespaces:
namespace game
{
	namespace graphics
	{
		// Classes:
		class vertexBufferObject : public bufferObject<FBOHandle>
		{
			public:
				// Constructor(s):
				vertexBufferObject();
				vertexBufferObject(const std::vector<GLfloat>& vertexData, GLenum usage);

				// Force this type to be move-only:
				vertexBufferObject(vertexBufferObject&& t) = default;
				//vertexBufferObject(const vertexBufferObject&) = delete;

				// Destructor(s):
				virtual ~vertexBufferObject();

				// Operator overloads:
				vertexBufferObject& operator=(vertexBufferObject&& input);

				// Methods:
				virtual bool init(const std::vector<std::vector<GLfloat>>& vertexDataArray, GLenum usage, bool destroyFirst=true);

				inline bool init(const std::vector<GLfloat>& vertexData, GLenum usage, bool destroyFirst=true)
				{
					auto input = std::vector<std::vector<GLfloat>>(1, vertexData);

					return init(input, usage, destroyFirst);
				}

				virtual void destroy(bool clear=true) override;
		};
	}
}