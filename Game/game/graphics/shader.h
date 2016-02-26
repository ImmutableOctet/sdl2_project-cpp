#pragma once

#include "types.h"

#include <string>

// Namespace(s):
namespace game
{
	namespace graphics
	{
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

				virtual bool build(const GLchar* vertex, const GLchar* fragment, shaderHandle* vertex_out = nullptr, shaderHandle* fragment_out = nullptr);

				inline bool build(const std::string& vertex, const std::string& fragment, shaderHandle* vertex_out = nullptr, shaderHandle* fragment_out = nullptr)
				{
					return build(vertex.c_str(), fragment.c_str(), vertex_out, fragment_out);
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
