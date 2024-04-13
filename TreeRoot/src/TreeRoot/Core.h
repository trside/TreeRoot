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

#ifdef TR_DEBUG
	#define TR_ENABLE_ASSERTS
#endif

#ifdef TR_ENABLE_ASSERTS
	#define TR_ASSERT(x, ...) { if(!(x)) { TR_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define TR_CORE_ASSERT(x, ...) { if(!(x)) { TR_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define TR_ASSERT(x, ...)
	#define TR_CORE_ASSERT(x, ...)
#endif

#define TR_BIND_EVENT(x) std::bind(&x, this, std::placeholders::_1)		// std::bind()方法绑定类成员函数时需要传入该对象本身的指针作为第二个参数，以确保绑定后的成员函数归属于这个对象，而在实际的调用时，传入的第一个参数是bind方法中的第三个参数