#pragma once

// Includes:
#include "types.h"
#include "buffer_object.h"

// Namespaces:
namespace game
{
	namespace graphics
	{
		// Classes:
		using vertexBufferObject = bufferObject<VBOHandle, GLfloat, GL_ARRAY_BUFFER>;
	}
}