#pragma once


#ifdef RUNE_PLATFORM_WINDOWS // TODO this macro does not exist yet
	#ifdef RUNE_BUILD_DLL
		#define RUNE_API __declspec(dllexport)
	#else 
		#define RUNE_API __declspec(dllimport)
	#endif
#else
	#error Rune is only currently supported on windows
#endif

#ifdef RUNE_ENABLE_ASSERTS
	#define RUNE_ASSERT(x, ...) { if(!(x)) { RUNE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define RUNE_CORE_ASSERT(x, ...) { if(!(x)) { RUNE_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define RUNE_ASSERT(x, ...)
	#define RUNE_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)