#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/ostr.h"

namespace Velocity
{

	class VELOCITY_API Log
	{
	public:
		static void Init();
		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}

// Core Macros
#define VL_CORE_TRACE(...) ::Velocity::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define VL_CORE_INFO(...) ::Velocity::Log::GetCoreLogger()->info(__VA_ARGS__)
#define VL_CORE_WARN(...) ::Velocity::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define VL_CORE_ERROR(...) ::Velocity::Log::GetCoreLogger()->error(__VA_ARGS__)
#define VL_CORE_FATAL(...) ::Velocity::Log::GetCoreLogger()->fatal(__VA_ARGS__)

#define VL_TRACE(...) ::Velocity::Log::GetClientLogger()->trace(__VA_ARGS__)
#define VL_INFO(...) ::Velocity::Log::GetClientLogger()->info(__VA_ARGS__)
#define VL_WARN(...) ::Velocity::Log::GetClientLogger()->warn(__VA_ARGS__)
#define VL_ERROR(...) ::Velocity::Log::GetClientLogger()->error(__VA_ARGS__)
#define VL_FATAL(...) ::Velocity::Log::GetClientLogger()->fatal(__VA_ARGS__)

// if dist build