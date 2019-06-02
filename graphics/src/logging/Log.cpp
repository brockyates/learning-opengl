#include "pch.h"
#include "Log.h"

#include <spdlog/sinks/ostream_sink.h>

namespace Graphics::Utils
{

    std::shared_ptr<spdlog::logger> Log::s_Logger;
    std::shared_ptr<spdlog::logger> Log::s_OpenGLLogger;
    std::ostringstream Log::s_LogStream;

    void Log::Init()
    {
        auto sink = std::make_shared<spdlog::sinks::ostream_sink_mt>(s_LogStream);
        const auto pattern = "%^[%T] [%l] [%n] %v%$";

        s_Logger = std::make_shared<spdlog::logger>("Graphics", sink);
        s_Logger->set_level(spdlog::level::trace);
        s_Logger->set_pattern(pattern);

        s_OpenGLLogger = std::make_shared<spdlog::logger>("OpenGL", sink);
        s_OpenGLLogger->set_level(spdlog::level::trace);
        s_OpenGLLogger->set_pattern(pattern);

        LOG_INFO("spdlog initialized");
    }
}
