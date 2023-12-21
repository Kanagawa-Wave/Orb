#pragma once

#pragma warning(push, 0)
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#pragma warning(pop)

namespace Orb
{
	class Log
	{
	public:
		static void Init();

		static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}


// Core log macros
#define CORE_TRACE(...)    ::Orb::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define CORE_INFO(...)     ::Orb::Log::GetCoreLogger()->info(__VA_ARGS__)
#define CORE_WARN(...)     ::Orb::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define CORE_ERROR(...)    ::Orb::Log::GetCoreLogger()->error(__VA_ARGS__)
#define CORE_CRITICAL(...) ::Orb::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define TRACE(...)         ::Orb::Log::GetClientLogger()->trace(__VA_ARGS__)
#define INFO(...)          ::Orb::Log::GetClientLogger()->info(__VA_ARGS__)
#define WARN(...)          ::Orb::Log::GetClientLogger()->warn(__VA_ARGS__)
#define ERROR(...)         ::Orb::Log::GetClientLogger()->error(__VA_ARGS__)
#define CRITICAL(...)      ::Orb::Log::GetClientLogger()->critical(__VA_ARGS__)

#define D3D_ASSERT(x, ...) { if(FAILED(x)) { CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define ASSERT(x, ...) { if(!(x)) { CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }