#pragma once

/*
	OpenGL simplification layer: Uniform
*/

// Includes:
#include "opengl.h"
#include "types.h"
#include "vertex.h"

//#include <GL/glew.h>

// STL:
#include <vector>
#include <stdexcept>
#include <type_traits>

// C STDLIB:
#include <cstddef>

// Namespace(s):
namespace game
{
	namespace graphics
	{
		// Functions:

		// GL API Wrapper:

		// OpenGL type constants:
		template <typename unsupported = std::enable_if<false>>
		inline constexpr GLenum getGLType() { return GL_FALSE; }

		template <> inline constexpr GLenum getGLType<bool>() { return GL_BOOL; } // GLboolean
		template <> inline constexpr GLenum getGLType<GLbyte>() { return GL_BYTE; }
		template <> inline constexpr GLenum getGLType<GLubyte>() { return GL_UNSIGNED_BYTE; }
		template <> inline constexpr GLenum getGLType<GLshort>() { return GL_SHORT; }
		template <> inline constexpr GLenum getGLType<GLushort>() { return GL_UNSIGNED_SHORT; }
		template <> inline constexpr GLenum getGLType<GLint>() { return GL_INT; }
		template <> inline constexpr GLenum getGLType<GLuint>() { return GL_UNSIGNED_INT; }
		template <> inline constexpr GLenum getGLType<GLfloat>() { return GL_FLOAT; }
		template <> inline constexpr GLenum getGLType<GLdouble>() { return GL_DOUBLE; }

		template <typename containerType>
		inline void destroyGLBuffers(containerType& instances, bool clear=true)
		{
			if (!instances.empty())
			{
				glDeleteBuffers(static_cast<GLsizei>(instances.size()), instances.data());

				if (clear)
				{
					instances.clear();
				}
			}
		}

		// This deletes the buffer located at 'instance', then sets 'instance' to 'empty'.
		template <typename handleType=GLuint, handleType empty=handleType()>
		inline void destroyGLBuffer(handleType& instance)
		{
			if (instance != empty)
			{
				glDeleteBuffers(1, &instance);

				instance = empty;
			}
		}

		// This deletes the buffer located at 'instance', but does not set it to 'empty'.
		// Essentially, this is called only when an r-value was used.
		template <typename handleType = GLuint, handleType empty = handleType()>
		inline void destroyGLBuffer(handleType&& instance) // handleType
		{
			if (instance != empty)
			{
				glDeleteBuffers(1, &instance);
			}
		}

		// This generates a set of managed buffers using OpenGL, and outputs them to 'instances'.
		template <typename T, typename handleType=GLuint>
		inline bool generateGLBuffers(std::vector<handleType>& instances, const std::vector<std::vector<T>>& inputDataset, GLenum usage, GLenum target)
		{
			// Get the current size, so we can use it as a starting index.
			auto startIndex = instances.size();

			// Allocate the extra memory we need.
			instances.resize(startIndex + inputDataset.size());

			// Point to the new area.
			EBOHandle* const raw_ptr = (instances.data() + startIndex);

			// Generate buffer handles.
			glGenBuffers(static_cast<GLsizei>(inputDataset.size()), raw_ptr);

			// Iterate over each provided entry:
			for (auto i = 0; i < inputDataset.size(); i++)
			{
				// Retrieve the current entry.
				const std::vector<T>& inputData = inputDataset[i];

				// Bind one of the buffers we generated.
				glBindBuffer(target, raw_ptr[i]);

				// Upload the buffer's contents to the GPU.
				glBufferData(target, sizeof(T) * inputData.size(), inputData.data(), usage);
			}

			// Return the default response.
			return true;
		}

		// The 'length' argument represents the number of entries in 'inputData', not the size in bytes.
		// To change this behavior, and instead use the size in bytes, set 'raw_length' to 'true'.
		template <typename T, typename handleType=GLuint>
		inline bool generateGLBuffer(handleType& instance, const T* inputData, GLsizei length, GLenum usage, GLenum target, bool should_unbind=true, bool raw_length=false)
		{
			// Generate buffer handles.
			glGenBuffers(1, &instance);

			// Bind one of the buffers we generated.
			glBindBuffer(target, instance);

			// Upload the buffer's contents to the GPU.
			glBufferData(target, ((raw_length) ? length : (sizeof(T) * length)), inputData, usage);

			if (should_unbind)
			{
				glBindBuffer(target, handleType());
			}

			// Return the default response.
			return true;
		}

		template <typename handleType=GLuint>
		inline bool generateGLBuffer(handleType& instance, const vertex_t* inputData, GLsizei length, GLenum usage, GLenum target, bool should_unbind = true, bool raw_length=false)
		{
			if (inputData == nullptr)
			{
				return false;
			}

			const auto& firstEntry = (*inputData);
			
			auto entryElements = firstEntry.elementCount();

			return generateGLBuffer(instance, static_cast<const GLfloat*>(firstEntry), length * static_cast<GLsizei>(entryElements), usage, target, should_unbind, raw_length);
		}

		// Shader related:
		inline void setUniform(shaderLocation attr, GLfloat value) { glUniform1f(attr, value); }
		inline void setUniform(shaderLocation attr, GLfloat x, GLfloat y) { glUniform2f(attr, x, y); }
		inline void setUniform(shaderLocation attr, GLfloat x, GLfloat y, GLfloat z) { glUniform3f(attr, x, y, z); }
		inline void setUniform(shaderLocation attr, GLfloat x, GLfloat y, GLfloat z, GLfloat w) { glUniform4f(attr, x, y, z, w); }

		inline void setUniform(shaderLocation attr, GLdouble value) { glUniform1d(attr, value); }
		inline void setUniform(shaderLocation attr, GLdouble x, GLdouble y) { glUniform2d(attr, x, y); }
		inline void setUniform(shaderLocation attr, GLdouble x, GLdouble y, GLdouble z) { glUniform3d(attr, x, y, z); }
		inline void setUniform(shaderLocation attr, GLdouble x, GLdouble y, GLdouble z, GLdouble w) { glUniform4d(attr, x, y, z, w); }

		inline void setUniform(shaderLocation attr, GLint value) { glUniform1i(attr, value); }
		inline void setUniform(shaderLocation attr, GLint x, GLint y) { glUniform2i(attr, x, y); }
		inline void setUniform(shaderLocation attr, GLint x, GLint y, GLint z) { glUniform3i(attr, x, y, z); }
		inline void setUniform(shaderLocation attr, GLint x, GLint y, GLint z, GLint w) { glUniform4i(attr, x, y, z, w); }

		inline void setUniform(shaderLocation attr, GLuint value) { glUniform1ui(attr, value); }
		inline void setUniform(shaderLocation attr, GLuint x, GLuint y) { glUniform2ui(attr, x, y); }
		inline void setUniform(shaderLocation attr, GLuint x, GLuint y, GLuint z) { glUniform3ui(attr, x, y, z); }
		inline void setUniform(shaderLocation attr, GLuint x, GLuint y, GLuint z, GLuint w) { glUniform4ui(attr, x, y, z, w); }

		inline void setVector1(shaderLocation attr, const GLfloat* values, GLsizei count = 1) { glUniform1fv(attr, count, values); }
		inline void setVector2(shaderLocation attr, const GLfloat* values, GLsizei count = 2) { glUniform2fv(attr, count, values); }
		inline void setVector3(shaderLocation attr, const GLfloat* values, GLsizei count = 3) { glUniform3fv(attr, count, values); }
		inline void setVector4(shaderLocation attr, const GLfloat* values, GLsizei count = 4) { glUniform4fv(attr, count, values); }

		inline void setVector1(shaderLocation attr, const GLdouble* values, GLsizei count = 1) { glUniform1dv(attr, count, values); }
		inline void setVector2(shaderLocation attr, const GLdouble* values, GLsizei count = 2) { glUniform2dv(attr, count, values); }
		inline void setVector3(shaderLocation attr, const GLdouble* values, GLsizei count = 3) { glUniform3dv(attr, count, values); }
		inline void setVector4(shaderLocation attr, const GLdouble* values, GLsizei count = 4) { glUniform4dv(attr, count, values); }

		inline void setVector1(shaderLocation attr, const GLint* values, GLsizei count = 1) { glUniform1iv(attr, count, values); }
		inline void setVector2(shaderLocation attr, const GLint* values, GLsizei count = 2) { glUniform2iv(attr, count, values); }
		inline void setVector3(shaderLocation attr, const GLint* values, GLsizei count = 3) { glUniform3iv(attr, count, values); }
		inline void setVector4(shaderLocation attr, const GLint* values, GLsizei count = 4) { glUniform4iv(attr, count, values); }

		inline void setVector1(shaderLocation attr, const GLuint* values, GLsizei count = 1) { glUniform1uiv(attr, count, values); }
		inline void setVector2(shaderLocation attr, const GLuint* values, GLsizei count = 2) { glUniform2uiv(attr, count, values); }
		inline void setVector3(shaderLocation attr, const GLuint* values, GLsizei count = 3) { glUniform3uiv(attr, count, values); }
		inline void setVector4(shaderLocation attr, const GLuint* values, GLsizei count = 4) { glUniform4uiv(attr, count, values); }

		// Abstraction layer:
		template <typename T, typename = std::enable_if_t<std::is_integral<T>::value || std::is_floating_point<T>::value>>
		inline void setVector(shaderLocation attr, T* values, GLsizei count)
		{
			switch (count)
			{
				case 1:
					setVector1(attr, values, count); break;
				case 2:
					setVector2(attr, values, count); break;
				case 3:
					setVector3(attr, values, count); break;
				case 4:
					setVector4(attr, values, count); break;
			}
		}
	}
}
