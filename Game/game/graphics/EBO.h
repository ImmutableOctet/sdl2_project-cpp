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
		using elementBufferObject = bufferObject<EBOHandle, GLuint, GL_ELEMENT_ARRAY_BUFFER>;
	}
}