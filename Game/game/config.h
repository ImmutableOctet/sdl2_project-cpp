#pragma once

// Preprocessor definitions:
#define _CRT_SECURE_NO_WARNINGS

#ifdef _DEBUG // NDEBUG
	#define GAME_DEBUG
#endif

#ifdef GAME_DEBUG
	#define GAME_CONSOLE
#endif

#if defined(_WIN32) || defined(WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
	#define PLATFORM_WINDOWS
#endif
