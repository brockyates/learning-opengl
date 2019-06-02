#pragma once
#include "spdlog/spdlog.h"

#include <memory>
#include <sstream>

namespace Graphics { namespace Utils {

    class Log
    {
    public:
        static void Init();

        static std::shared_ptr<spdlog::logger>& GetLogger() { return s_Logger; }
        static std::shared_ptr<spdlog::logger>& GetOpenGLLogger() { return s_OpenGLLogger; }

        static const std::ostringstream& GetLogStream() { return s_LogStream; }

    private:
        static std::shared_ptr<spdlog::logger> s_Logger;
        static std::shared_ptr<spdlog::logger> s_OpenGLLogger;
        static std::ostringstream s_LogStream;
    };

}}

#ifdef APP_DEBUG
    #define APP_ENABLE_LOGGING
#endif // APP_DEBUG

#ifdef APP_ENABLE_LOGGING
    // Application Log macros
    #define LOG_TRACE(...)           ::Graphics::Utils::Log::GetLogger()->trace(__VA_ARGS__)
    #define LOG_INFO(...)            ::Graphics::Utils::Log::GetLogger()->info(__VA_ARGS__)
    #define LOG_WARN(...)            ::Graphics::Utils::Log::GetLogger()->warn(__VA_ARGS__)
    #define LOG_ERROR(...)           ::Graphics::Utils::Log::GetLogger()->error(__VA_ARGS__)
    #define LOG_DEBUG(...)           ::Graphics::Utils::Log::GetLogger()->debug(__VA_ARGS__)
    #define LOG_CRITICAL(...)        ::Graphics::Utils::Log::GetLogger()->critical(__VA_ARGS__)

    // OpenGL Log macros
    #define LOG_GL_TRACE(...)        ::Graphics::Utils::Log::GetOpenGLLogger()->trace(__VA_ARGS__)
    #define LOG_GL_INFO(...)         ::Graphics::Utils::Log::GetOpenGLLogger()->info(__VA_ARGS__)
    #define LOG_GL_WARN(...)         ::Graphics::Utils::Log::GetOpenGLLogger()->warn(__VA_ARGS__)
    #define LOG_GL_ERROR(...)        ::Graphics::Utils::Log::GetOpenGLLogger()->error(__VA_ARGS__)
    #define LOG_GL_DEBUG(...)        ::Graphics::Utils::Log::GetOpenGLLogger()->debug(__VA_ARGS__)
    #define LOG_GL_CRITICAL(...)     ::Graphics::Utils::Log::GetOpenGLLogger()->critical(__VA_ARGS__)
#else
    // Application Log macros
    #define LOG_TRACE(...)
    #define LOG_INFO(...)
    #define LOG_WARN(...)
    #define LOG_ERROR(...)
    #define LOG_DEBUG(...)
    #define LOG_CRITICAL(...)

    // OpenGL Log macros
    #define LOG_GL_TRACE(...)
    #define LOG_GL_INFO(...)
    #define LOG_GL_WARN(...)
    #define LOG_GL_ERROR(...)
    #define LOG_GL_DEBUG(...)
    #define LOG_GL_CRITICAL(...)
#endif // APP_ENABLE_LOGGING
