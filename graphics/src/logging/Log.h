#pragma once
#include "spdlog/spdlog.h"

#include <memory>
#include <sstream>

namespace graphics { namespace utils {

    class Log
    {
    public:
        static void Init();

        inline static std::shared_ptr<spdlog::logger>& GetLogger() { return s_Logger; }
        inline static std::shared_ptr<spdlog::logger>& GetOpenGLLogger() { return s_OpenGLLogger; }

        inline static const std::ostringstream& GetLogStream() { return s_LogStream; }

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
    #define LOG_TRACE(...)           ::graphics::utils::Log::GetLogger()->trace(__VA_ARGS__)
    #define LOG_INFO(...)            ::graphics::utils::Log::GetLogger()->info(__VA_ARGS__)
    #define LOG_WARN(...)            ::graphics::utils::Log::GetLogger()->warn(__VA_ARGS__)
    #define LOG_ERROR(...)           ::graphics::utils::Log::GetLogger()->error(__VA_ARGS__)
    #define LOG_DEBUG(...)           ::graphics::utils::Log::GetLogger()->debug(__VA_ARGS__)
    #define LOG_CRITICAL(...)        ::graphics::utils::Log::GetLogger()->critical(__VA_ARGS__)

    // OpenGL Log macros
    #define LOG_GL_TRACE(...)        ::graphics::utils::Log::GetOpenGLLogger()->trace(__VA_ARGS__)
    #define LOG_GL_INFO(...)         ::graphics::utils::Log::GetOpenGLLogger()->info(__VA_ARGS__)
    #define LOG_GL_WARN(...)         ::graphics::utils::Log::GetOpenGLLogger()->warn(__VA_ARGS__)
    #define LOG_GL_ERROR(...)        ::graphics::utils::Log::GetOpenGLLogger()->error(__VA_ARGS__)
    #define LOG_GL_DEBUG(...)        ::graphics::utils::Log::GetOpenGLLogger()->debug(__VA_ARGS__)
    #define LOG_GL_CRITICAL(...)     ::graphics::utils::Log::GetOpenGLLogger()->critical(__VA_ARGS__)
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
