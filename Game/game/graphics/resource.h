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
		template <typename resourceHandle, resourceHandle noinstance_value=resourceHandle()>
		class resource
		{
			public:
				// Typedefs:
				using resourceHandle_t = resourceHandle;

				// Constant variable(s):
				static const resourceHandle_t noinstance = noinstance_value;

				// Constructor(s):
				resource() = default;
				resource(const resource&) = delete;
				
				inline resource(resource&& rval)
				{
					*this = std::move(rval);
				}

				// Destructor(s):
				inline virtual ~resource() { /* This destructor cannot call 'destroy'. */ }

				// Operator overloads:
				inline resource& operator=(resource&& rval)
				{
					destroy();

					//std::swap(this->instance, rval.instance);

					this->instance = std::move(rval.instance);
					rval.instance = noinstance;

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
				resourceHandle_t instance = noinstance;
		};

		// Structures:
		template <typename resourceType>
		class resource_lock
		{
			public:
				// Typedefs:
				using resourceType_t = resourceType;
				//using resourceHandle_t = resourceType::resourceHandle_t;
			protected:
				// Fields:
				const resourceType* resource_ref = nullptr;
			public:
				// Constructor(s):
				resource_lock() = delete;
				resource_lock(const resource_lock&) = delete;

				inline resource_lock(const resourceType_t* rptr) : resource_ref(rptr)
				{
					bind();
				}
				
				inline resource_lock(const resourceType_t& ref) : resource_lock(&ref) { /* Nothing so far. */ }

				inline resource_lock(resource_lock&& res) // = default
				{
					std::swap(this->resource_ref, res.resource_ref);
				}

				// Destructor(s):
				inline ~resource_lock()
				{
					unbind();
				}

				// Methods:
				inline virtual void bind() // const
				{
					if (resource_ref == nullptr)
					{
						return;
					}

					resource_ref->bind();

					return;
				}

				inline virtual void unbind() // const
				{
					if (resource_ref == nullptr)
					{
						return;
					}

					resource_ref->unbind();

					return;
				}

				inline resourceType_t& getReference() const
				{
					return *resource_ref;
				}
		};
	}
}