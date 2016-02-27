#pragma once

#include "types.h"

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
			protected:
				bufferHandle_t instance;
		};
	}
}