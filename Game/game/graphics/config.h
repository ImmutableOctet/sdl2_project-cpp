#pragma once

// Includes:
#include "../compiler_config.h"

#ifdef GAME_DEBUG
	#define SHADER_LOCK_SAFE
#endif

#ifdef SHADER_LOCK_SAFE
	#define SHADER_LOCK_LEGACY
#endif
