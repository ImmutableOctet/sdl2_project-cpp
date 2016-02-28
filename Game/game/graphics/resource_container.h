#pragma once

#include "types.h"

// STL:
#include <vector>

// C STDLIB:
#include <cstddef>

namespace game
{
	namespace graphics
	{
		template <typename resourceHandle_t>
		class resourceContainer
		{
			public:
				// Constructor(s):
				inline resourceContainer() {}

				// Operator overloads:
				inline resourceHandle_t operator[](std::size_t index) const
				{
					return instances[index];
				}

				inline bool operator==(const resourceHandle_t& inst) const
				{
					for (const auto& handle : instances)
					{
						if (handle == inst)
						{
							return true;
						}
					}

					// Return the default response.
					return false;
				}

				inline bool operator==(const std::vector<resourceHandle_t>& insts) const
				{
					return (insts == instances);
				}

				// Methods:
				inline const std::vector<resourceHandle_t>& getInstances() const
				{
					return instances;
				}

				// Abstract:
				virtual void destroy(bool clear = true) = 0;
			protected:
				// Fields:
				std::vector<resourceHandle_t> instances;
		};
	}
}