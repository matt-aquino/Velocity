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