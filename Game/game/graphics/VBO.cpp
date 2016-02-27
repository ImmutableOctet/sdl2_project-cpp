#include "VBO.h"
#include "opengl.h"

// Namespace(s):
namespace game
{
	namespace graphics
	{
		// Classes:

		// vertexBufferObject:

		// Constructor(s):
		vertexBufferObject::vertexBufferObject()
		{
			// Nothing so far.
		}

		// Destructor(s):
		vertexBufferObject::~vertexBufferObject()
		{
			// Nothing so far.
		}

		// Methods:
		bool vertexBufferObject::init(const std::vector<std::vector<GLfloat>>& vertexDataArray, GLenum usage, bool destroyFirst)
		{
			if (destroyFirst)
			{
				destroy(true);
			}

			auto startIndex = instances.size();
			instances.resize(startIndex + vertexDataArray.size());

			FBOHandle* raw_ptr = instances.data();

			glGenBuffers(static_cast<GLsizei>(vertexDataArray.size()), raw_ptr);

			for (auto i = 0; i < vertexDataArray.size(); i++)
			{
				const std::vector<GLfloat>& vertexData = vertexDataArray[i];

				glBindBuffer(GL_ARRAY_BUFFER, raw_ptr[i]);
				glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertexData.size(), vertexData.data(), usage);
			}

			// Return the default response.
			return true;
		}
	}
}
