#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace tr {

	class Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger;  }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}

// Core log macros
#define TR_CORE_TRACE(...)		::tr::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define TR_CORE_INFO(...)		::tr::Log::GetCoreLogger()->info(__VA_ARGS__)
#define TR_CORE_WARN(...)		::tr::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define TR_CORE_ERROR(...)		::tr::Log::GetCoreLogger()->error(__VA_ARGS__)
#define TR_CORE_FATAL(...)		::tr::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client log macros
#define TR_TRACE(...)			::tr::Log::GetClientLogger()->trace(__VA_ARGS__)
#define TR_INFO(...)			::tr::Log::GetClientLogger()->info(__VA_ARGS__)
#define TR_WARN(...)			::tr::Log::GetClientLogger()->warn(__VA_ARGS__)
#define TR_ERROR(...)			::tr::Log::GetClientLogger()->error(__VA_ARGS__)
#define TR_FATAL(...)			::tr::Log::GetClientLogger()->fatal(__VA_ARGS__)

