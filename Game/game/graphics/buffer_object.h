#pragma once

// Includes:
#include "resource.h"
#include "uniform.h"

// STL:
#include <utility>
#include <stdexcept>
#include <vector>

// Namespace(s):
namespace game
{
	namespace graphics
	{
		template <typename resourceHandle_t, typename dataType, GLenum target, resourceHandle_t noinstance_value = resourceHandle_t()>
		class bufferObject : public resource<resourceHandle_t, noinstance_value>
		{
			private:
				// Typedefs:
				using super = resource<resourceHandle_t, noinstance_value>;
			public:

				// Constructor(s):
				inline bufferObject() { /* Nothing so far. */  }
				
				inline bufferObject(const dataType* indexData, GLenum usage)
				{
					if (!init(indexData, usage))
					{
						throw std::runtime_error("Failed to initialize buffer-object using raw data.");
					}
				}

				inline bufferObject(const std::vector<dataType>& indexData, GLenum usage)
				{
					if (!init(indexData, usage))
					{
						throw std::runtime_error("Failed to initialize buffer-object using 'std::vector'.");
					}
				}

				// Force this type to be move-only:
				//bufferObject(const buferObject& buffer) = delete;
				bufferObject(bufferObject&& buffer) = default;

				// Destructor(s):
				inline ~bufferObject()
				{
					destroy();
				}

				// Operator overloads:
				bufferObject& operator=(bufferObject&&) = default;

				/*
					inline bufferObject& operator=(bufferObject&& input)
					{
						resource::operator=(input);

						return *this;
					}
				*/

				// Methods:
				inline bool init(const dataType* indexData, GLsizei length, GLenum usage, bool should_unbind=true, bool useLengthInBytes=false)
				{
					return generateGLBuffer(this->instance, indexData, length, usage, target, should_unbind, useLengthInBytes);
				}

				inline bool init(const std::vector<dataType>& indexData, GLenum usage, bool should_unbind=true, bool useLengthInBytes=false)
				{
					return init(indexData.data(), static_cast<GLsizei>(indexData.size()), usage, useLengthInBytes);
				}

				inline void destroy() override
				{
					if (instance != noinstance)
					{
						destroyGLBuffer(instance);

						instance = noinstance;
					}

					return;
				}

				inline void bind() const override
				{
					glBindBuffer(target, this->instance);

					return;
				}

				inline void unbind() const override
				{
					glBindBuffer(target, noinstance);

					return;
				}
		};
	}
}