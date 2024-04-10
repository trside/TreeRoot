#pragma once

#ifdef TR_PLATFORM_WINDOWS
	#ifdef TR_BUILD_DLL
		#define TR_API __declspec(dllexport)
	#else
		#define TR_API __declspec(dllimport)
	#endif
#else 
	#error TreeRoot only supports Windows!
#endif

#define BIT(x) (1 << x)

#ifdef TR_ENABLE_ASSERTS
	#define TR_ASSERT(x, ...) { if(!(x)) { TR_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define TR_CORE_ASSERT(x, ...) { if(!(x)) { TR_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define TR_ASSERT(x, ...)
	#define TR_CORE_ASSERT(x, ...)
#endif