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
		template <typename bufferHandle_t>
		class bufferObject
		{
			public:
				// Constant variable(s):
				static const bufferHandle_t noinstance = bufferHandle_t();

				// Constructor(s):
				inline bufferObject() {}

				// Operator overloads:
				inline bufferHandle_t operator[](std::size_t index) const
				{
					return instances[index];
				}

				bool operator==(const bufferHandle_t& inst) const
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

				bool operator==(const std::vector<bufferHandle_t>& insts) const
				{
					return (insts == instances);
				}

				// Methods:
				inline const std::vector<bufferHandle_t>& getInstances() const
				{
					return instances;
				}

				// Abstract:
				virtual void destroy(bool clear = true) = 0;
			protected:
				// Fields:
				std::vector<bufferHandle_t> instances;
		};
	}
}