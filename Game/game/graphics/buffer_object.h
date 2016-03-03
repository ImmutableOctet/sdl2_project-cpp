#pragma once

// Includes:
#include "resource.h"
#include "uniform.h"

// STL:
#include <utility>
#include <stdexcept>

// C STDLIB:
#include <cstddef>

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
			protected:
				// Fields:
				std::size_t count = 0;
			public:
				// Typedefs:
				using type = dataType;

				// Constructor(s):
				inline bufferObject() { /* Nothing so far. */  }
				
				inline bufferObject(const dataType* indexData, GLenum usage)
				{
					if (!init(indexData, usage))
					{
						throw std::runtime_error("Failed to initialize buffer-object using raw data.");
					}
				}

				template <typename containerType>
				inline bufferObject(const containerType& indexData, GLenum usage)
				{
					if (!init(indexData, usage))
					{
						throw std::runtime_error("Failed to initialize buffer-object using a generic container.");
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
				inline bool init(const dataType* data, GLsizei length, GLenum usage, bool should_unbind=true, bool useLengthInBytes=false)
				{
					// Before anything else, make sure we don't have any existing content:
					if (exists())
					{
						return false;
					}

					bool response = generateGLBuffer(this->instance, data, length, usage, target, should_unbind, useLengthInBytes);

					if (response)
					{
						if (useLengthInBytes)
						{
							this->count = (length / sizeof(dataType));
						}
						else
						{
							this->count = length;
						}
					}

					return response;
				}

				template <typename containerType> // contentType=dataType
				inline bool init(const containerType& indexData, GLenum usage, bool should_unbind=true, bool __useLengthInBytes=false)
				{
					return init(indexData.data(), static_cast<GLsizei>(indexData.size()), usage, __useLengthInBytes);
				}

				inline void destroy() override
				{
					if (instance != noinstance)
					{
						destroyGLBuffer(instance);

						instance = noinstance;

						count = 0;
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

				// This reports the number of elements of size 'dataType' in this buffer-object.
				inline std::size_t size() const
				{
					return count;
				}
		};
	}
}