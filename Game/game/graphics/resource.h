#pragma once

#include "types.h"

// STL:
#include <type_traits>

namespace game
{
	namespace graphics
	{
		template <typename resourceHandle_t, resourceHandle_t noinstance_value=resourceHandle_t()>
		class resource
		{
			public:
				// Constant variable(s):
				static const resourceHandle_t noinstance = noinstance_value;

				// Operator overloads:
				template <typename T = std::enable_if<std::is_base_of<resource, T>::value>::type>
				inline resource& operator=(T&& input)
				{
					destroy();

					std::swap(this->instance, input.instance);

					return *this;
				}

				inline bool operator==(const resourceHandle_t& inst) const
				{
					return (inst == instance);
				}

				// Methods:
				inline const resourceHandle_t& getInstance() const
				{
					return instance;
				}

				inline bool exists() const
				{
					return (instance != noinstance);
				}

				// Abstract:
				virtual void destroy() = 0;

				virtual void bind() const = 0;
				virtual void unbind() const = 0;
			protected:
				// Fields:
				resourceHandle_t instance;
		};
	}
}