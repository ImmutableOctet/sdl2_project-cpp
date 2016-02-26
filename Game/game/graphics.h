#pragma once

// Includes:

// OpenGL / SDL:
#include <SDL.h>
#include <GL/glew.h>
#include <SDL_opengl.h>
#include <GL/glu.h>

// STL:
#include <string>

// Namespace(s):
namespace game
{
	namespace graphics
	{
		// Typedefs:
		using context = SDL_GLContext;

		using shaderHandle = GLuint;
		using shaderLocation = GLint;

		// Constant variable(s):
		static const context nocontext = nullptr;
		
		// Structures:
		struct contextInfo
		{
			// Nothing so far.
		};

		// Functions:

		// Support layer:

		// This configures OpenGL contexts.
		// Please call this before calling 'initializeGL',
		// or use the 'autocfg' argument of that function.
		void configureGL();

		/*
			This initializes OpenGL.

			DO NOT use the OpenGL API before this is called.

			Most applications automatically call this
			before initializing graphical behavior.

			The 'autocfg' argument should be 'true'
			the first time this is called.

			That argument ensures a call to the 'configureGL'
			command, which may or may not be required.
		*/

		bool initializeGL(bool experimental=true, bool autocfg=true);

		/*
			This deinitializes OpenGL.
			
			DO NOT call this without first calling 'initializeGL'.
			In addition, DO NOT use any OpenGL APIs after calling this function.
		*/

		void deinitializeGL();

		// GL API Wrapper:
		inline void setUniform(shaderLocation attr, GLfloat value);
		inline void setUniform(shaderLocation attr, GLfloat x, GLfloat y);
		inline void setUniform(shaderLocation attr, GLfloat x, GLfloat y, GLfloat z);
		inline void setUniform(shaderLocation attr, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
		
		inline void setUniform(shaderLocation attr, GLdouble value);
		inline void setUniform(shaderLocation attr, GLdouble x, GLdouble y);
		inline void setUniform(shaderLocation attr, GLdouble x, GLdouble y, GLdouble z);
		inline void setUniform(shaderLocation attr, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
		
		inline void setUniform(shaderLocation attr, GLint value);
		inline void setUniform(shaderLocation attr, GLint x, GLint y);
		inline void setUniform(shaderLocation attr, GLint x, GLint y, GLint z);
		inline void setUniform(shaderLocation attr, GLint x, GLint y, GLint z, GLint w);
		
		inline void setUniform(shaderLocation attr, GLuint value);
		inline void setUniform(shaderLocation attr, GLuint x, GLuint y);
		inline void setUniform(shaderLocation attr, GLuint x, GLuint y, GLuint z);
		inline void setUniform(shaderLocation attr, GLuint x, GLuint y, GLuint z, GLuint w);

		inline void setVector1(shaderLocation attr, GLfloat* values, GLsizei count = 1) { glUniform1fv(attr, count, values); }
		inline void setVector2(shaderLocation attr, GLfloat* values, GLsizei count = 2) { glUniform2fv(attr, count, values); }
		inline void setVector3(shaderLocation attr, GLfloat* values, GLsizei count = 3) { glUniform3fv(attr, count, values); }
		inline void setVector4(shaderLocation attr, GLfloat* values, GLsizei count = 4) { glUniform4fv(attr, count, values); }

		inline void setVector1(shaderLocation attr, GLdouble* values, GLsizei count = 1) { glUniform1dv(attr, count, values); }
		inline void setVector2(shaderLocation attr, GLdouble* values, GLsizei count = 2) { glUniform2dv(attr, count, values); }
		inline void setVector3(shaderLocation attr, GLdouble* values, GLsizei count = 3) { glUniform3dv(attr, count, values); }
		inline void setVector4(shaderLocation attr, GLdouble* values, GLsizei count = 4) { glUniform4dv(attr, count, values); }

		inline void setVector1(shaderLocation attr, GLint* values, GLsizei count = 1) { glUniform1iv(attr, count, values); }
		inline void setVector2(shaderLocation attr, GLint* values, GLsizei count = 2) { glUniform2iv(attr, count, values); }
		inline void setVector3(shaderLocation attr, GLint* values, GLsizei count = 3) { glUniform3iv(attr, count, values); }
		inline void setVector4(shaderLocation attr, GLint* values, GLsizei count = 4) { glUniform4iv(attr, count, values); }

		inline void setVector1(shaderLocation attr, GLuint* values, GLsizei count = 1) { glUniform1uiv(attr, count, values); }
		inline void setVector2(shaderLocation attr, GLuint* values, GLsizei count = 2) { glUniform2uiv(attr, count, values); }
		inline void setVector3(shaderLocation attr, GLuint* values, GLsizei count = 3) { glUniform3uiv(attr, count, values); }
		inline void setVector4(shaderLocation attr, GLuint* values, GLsizei count = 4) { glUniform4uiv(attr, count, values); }

		// Classes:
		class shader
		{
			public:
				// Typedefs:
				using location = shaderLocation;

				// Constant variable(s):
				static const shaderHandle noinstance = 0;

				// Functions:
				static shaderHandle buildProgram(const GLchar* str, GLenum shaderType);
				
				inline static shaderHandle buildProgram(const std::string& str, GLenum shaderType)
				{
					return buildProgram(str.c_str(), shaderType);
				}

				// Constructor(s):
				shader();
				shader(const std::string& vertex, const std::string& fragment);

				// Force this type to be move-only:
				shader(shader&& s) = default;

				// Destructor(s):
				virtual ~shader();

				// Operator overloads:
				shader& operator=(shader&& input);

				inline bool operator==(shaderHandle inst) const
				{
					return (this->instance == inst);
				}

				// Methods:

				/*
					The 'vertex_out' and 'fragment_out' arguments may be used to pass handles to compiled shaders.
					
					If these arguments are specified, the shaders will not be disposed of, and will instead be given to the user.
					In contrast, if even one of the two arguments is ignored, then the shaders will be deleted properly.
					In addition, the two handles will be set to 'noinstance'.
				*/

				virtual void build(const GLchar* vertex, const GLchar* fragment, shaderHandle* vertex_out=nullptr, shaderHandle* fragment_out=nullptr);
				
				inline void build(const std::string& vertex, const std::string& fragment, shaderHandle* vertex_out=nullptr, shaderHandle* fragment_out=nullptr)
				{
					build(vertex.c_str(), fragment.c_str(), vertex_out, fragment_out);

					return;
				}

				virtual void destroy();

				// This retrieves a 'location' representing an attribute.
				// Attributes are commonly uniform' variables.
				inline location getAttribute(const GLchar* name)
				{
					return glGetAttribLocation(instance, name);
				}

				inline bool exists() const
				{
					return (instance != noinstance);
				}

				inline shaderHandle getInstance() const
				{
					return instance;
				}
			protected:
				//shader(const shader&); // = delete;

				// Fields:
				shaderHandle instance = noinstance;
		};
	}
}
