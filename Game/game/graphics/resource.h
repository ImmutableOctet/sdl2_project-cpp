#pragma once

#include "types.h"

// STL:
#include <type_traits>
#include <utility>

namespace game
{
	namespace graphics
	{
		// Classes:
		template <typename resourceHandle_t, resourceHandle_t noinstance_value=resourceHandle_t()>
		class resource
		{
			public:
				// Constant variable(s):
				static const resourceHandle_t noinstance = noinstance_value;

				// Destructor(s):
				virtual ~resource() = 0;

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

		// Structures:
		template <typename resourceType>
		class resource_lock
		{
			protected:
				const resourceType* resource_ref = nullptr;
			public:
				resource_lock() = delete;
				resource_lock(const resource_lock&) = delete;

				inline resource_lock(const resourceType* rptr) : resource_ref(rptr)
				{
					bind();
				}
				
				inline resource_lock(const resourceType& ref) : resource_lock(&ref) { /* Nothing so far. */ }

				inline resource_lock(resource_lock&& res) // = default
				{
					std::swap(this->resource_ref, res.resource_ref);
				}

				inline ~resource_lock()
				{
					unbind();
				}

				// Methods:
				inline void bind() const
				{
					if (resource_ref == nullptr)
					{
						return;
					}

					resource_ref->bind();

					return;
				}

				inline void unbind() const
				{
					if (resource_ref == nullptr)
					{
						return;
					}

					resource_ref->unbind();

					return;
				}

				inline resourceType& getReference() const
				{
					return *resource_ref;
				}
		};
	}
}