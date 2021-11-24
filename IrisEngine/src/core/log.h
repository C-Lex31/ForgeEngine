#pragma once



#include <memory>
#include "core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"
namespace Iris {

	class IRIS_API Log
	{
	public:
		static void Init();
		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_coreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_clientLogger; }
	private:
		static std::shared_ptr<spdlog::logger>s_coreLogger;
		static std::shared_ptr<spdlog::logger>s_clientLogger;

	};


}

#define IR_CORE_TRACE(...)  ::Iris::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define IR_CORE_INFO(...)   ::Iris::Log::GetCoreLogger()->info(__VA_ARGS__)
#define IR_CORE_WARN(...)   ::Iris::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define IR_CORE_ERROR(...)  ::Iris::Log::GetCoreLogger()->error(__VA_ARGS__)
#define IR_CORE_FATAL(...)  ::Iris::Log::GetCoreLogger()->fatal(__VA_ARGS__)


#define IR_TRACE(...)  ::Iris::Log::GetClientLogger()->trace(__VA_ARGS__)
#define IR_INFO(...)   ::Iris::Log::GetClientLogger()->info(__VA_ARGS__)
#define IR_WARN(...)   ::Iris::Log::GetClientLogger()->warn(__VA_ARGS__)
#define IR_ERROR(...)  ::Iris::Log::GetClientLogger()->error(__VA_ARGS__)
#define IR_FATAL(...)  ::Iris::Log::GetClientLogger()->fatal(__VA_ARGS__)