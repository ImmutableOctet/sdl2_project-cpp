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

		// Constant variable(s):
		static const context nocontext = nullptr;
		
		// Structures:
		struct contextInfo
		{
			// Nothing so far.
		};

		// Functions:

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

		// Classes:
		class shader
		{
			public:
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

				// Force objects to be move-only.
				shader(shader&& s) = default;

				// Destructor(s):
				virtual ~shader();

				// Operator overloads:
				inline bool operator==(shaderHandle inst) const
				{
					return (this->instance == inst);
				}

				// Methods:
				virtual void build(const GLchar* vertex, const GLchar* fragment);
				
				inline void build(const std::string& vertex, const std::string& fragment)
				{
					build(vertex.c_str(), fragment.c_str());

					return;
				}

				virtual void destroy();

				inline shaderHandle getInstance() const
				{
					return instance;
				}
			protected:
				// Fields:
				shaderHandle instance = noinstance;
		};
	}
}
