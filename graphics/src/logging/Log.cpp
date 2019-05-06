#include "pch.h"
#include "Log.h"

#include <spdlog/fmt/ostr.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Graphics { namespace Utils {

    std::shared_ptr<spdlog::logger> Log::s_Logger;
    std::shared_ptr<spdlog::logger> Log::s_OpenGLLogger;

    void Log::Init()
    {
        spdlog::set_pattern("%^[%T] [%n]: %v%$");

        s_Logger = spdlog::stdout_color_mt("Graphics");
        s_Logger->set_level(spdlog::level::trace);

        s_OpenGLLogger = spdlog::stdout_color_mt("OpenGL");
        s_OpenGLLogger->set_level(spdlog::level::trace);

        LOG_INFO("spdlog initialized");
    }

}}
