#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

#include "Rune/Core/Core.h"



namespace Rune {
	class RUNE_API Log {
	public:
		static void Init();

		inline static Ref<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static Ref<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static Ref<spdlog::logger> s_CoreLogger;
		static Ref<spdlog::logger> s_ClientLogger;
	};
}

// core log macros
#define RUNE_CORE_TRACE(...)   ::Rune::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define RUNE_CORE_INFO(...)    ::Rune::Log::GetCoreLogger()->info(__VA_ARGS__)
#define RUNE_CORE_WARN(...)    ::Rune::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define RUNE_CORE_ERROR(...)   ::Rune::Log::GetCoreLogger()->error(__VA_ARGS__)
#define RUNE_CORE_CRITICAL(...)::Rune::Log::GetCoreLogger()->critical(__VA_ARGS__)


#define RUNE_TRACE(...)        ::Rune::Log::GetClientLogger()->trace(__VA_ARGS__)
#define RUNE_INFO(...)         ::Rune::Log::GetClientLogger()->info(__VA_ARGS__)
#define RUNE_WARN(...)         ::Rune::Log::GetClientLogger()->warn(__VA_ARGS__)
#define RUNE_ERROR(...)        ::Rune::Log::GetClientLogger()->error(__VA_ARGS__)
#define RUNE_CRITICAL(...)     ::Rune::Log::GetClientLogger()->critical(__VA_ARGS__)

