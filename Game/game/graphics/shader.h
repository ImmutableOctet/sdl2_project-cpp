#pragma once

#include "resource.h"

#include <string>

// Namespace(s):
namespace game
{
	namespace graphics
	{
		// Classes:
		class shader : public resource<shaderHandle>
		{
			private:
				// Typedefs:
				using super = resource<shaderHandle>;
			public:
				// Typedefs:
				using location = shaderLocation;

				using lock = resource_lock<shader>;

				// Functions:
				static shaderHandle buildProgram(const GLchar* str, GLenum shaderType, GLchar* log_out=nullptr, GLsizei log_maxLength=0);

				inline static shaderHandle buildProgram(const std::string& str, GLenum shaderType, GLchar* log_out=nullptr, GLsizei log_maxLength=0)
				{
					return buildProgram(str.c_str(), shaderType, log_out, log_maxLength);
				}

				// Constructor(s):
				shader();
				shader(const std::string& vertex, const std::string& fragment);

				// Force this type to be move-only:
				//shader(const shader&) = delete;
				shader(shader&&) = default;

				// Destructor(s):
				virtual ~shader();

				// Operator overloads:
				shader& operator=(shader&&) = default;

				operator resourceHandle_t() const;

				// Methods:

				/*
					The 'vertex_out' and 'fragment_out' arguments may be used to pass handles to compiled shaders.

					If these arguments are specified, the shaders will not be disposed of, and will instead be given to the user.
					In contrast, if even one of the two arguments is ignored, then the shaders will be deleted properly.
					In addition, the two handles will be set to 'noinstance'.
				*/

				virtual bool build(const GLchar* vertex, const GLchar* fragment, GLchar* log_out=nullptr, GLsizei log_maxLength=0, shaderHandle* vertex_out=nullptr, shaderHandle* fragment_out=nullptr);

				inline bool build(const std::string& vertex, const std::string& fragment, GLchar* log_out=nullptr, GLsizei log_maxLength=0, shaderHandle* vertex_out=nullptr, shaderHandle* fragment_out=nullptr)
				{
					return build(vertex.c_str(), fragment.c_str(), log_out, log_maxLength, vertex_out, fragment_out);
				}

				virtual void destroy() override;

				virtual void bind() const override;
				virtual void unbind() const override;

				// This retrieves a 'location' representing an attribute.
				// Attributes are commonly uniform' variables.
				inline location getAttribute(const GLchar* name)
				{
					return glGetAttribLocation(instance, name);
				}
		};
	}
}
