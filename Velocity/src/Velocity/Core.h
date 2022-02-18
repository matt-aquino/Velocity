#pragma once

#ifdef VL_PLATFORM_WINDOWS
	#ifdef VL_BUILD_DLL
		#define VELOCITY_API __declspec(dllexport)
	#else
		#define VELOCITY_API __declspec(dllimport)
	#endif

#else
	#error Velocity only supports Windows!

#endif

#ifdef VL_ENABLE_ASSERTS
	#define VL_ASSERT(x, ...) { if(!(x)) { VL_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }}
	#define VL_CORE_ASSERT(x, ...) { if(!(x)) { VL_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }}

#else
	#define VL_ASSERT(x, ...)
	#define VL_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)