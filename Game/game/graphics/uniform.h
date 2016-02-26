#pragma once

// Includes:
#include "types.h"

#include <GL/glew.h>

// Namespace(s):
namespace game
{
	namespace graphics
	{
		// Functions:

		// GL API Wrapper:
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
		template <typename T, typename = std::enable_if_t<std::is_integral<T>::value> || std::enable_if_t<std::is_floating_point<T>::value>>
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
