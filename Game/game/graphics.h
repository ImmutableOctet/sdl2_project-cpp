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

				// This retrieves a 'shaderLocation' representing an attribute.
				// Attributes are commonly uniform' variables.
				shaderLocation getAttribute(const GLchar* name);

				bool setFloat(shaderLocation location, GLfloat value);

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
