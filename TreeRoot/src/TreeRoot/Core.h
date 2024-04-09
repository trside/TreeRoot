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