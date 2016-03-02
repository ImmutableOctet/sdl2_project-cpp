#pragma once

// Includes:
#include <SDL.h>

// Namespace(s):
namespace game
{
	namespace graphics
	{
		// Typedefs:
		using context = SDL_GLContext;

		// Constant variable(s):
		static const context nocontext = nullptr;

		// Structures:
		struct contextInfo
		{
			GLint max_attributes;
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

		// This retrieves a 'contextInfo' object using the current graphical context.
		void getContextInfo(contextInfo& renderInfo_out);
	}
}