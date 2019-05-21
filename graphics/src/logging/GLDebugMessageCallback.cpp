#include "pch.h"
#include "GLDebugMessageCallback.h"

namespace Graphics {

    namespace {

        void WriteLogToFile()
        {
            const auto t = std::time(nullptr);
            const auto utcTime = *std::gmtime(&t);

            std::stringstream ss;
            ss << "../bin/logs/GraphicsLog" << std::put_time(&utcTime, "%Y%m%d_%H%M%S") << ".txt";

            std::filesystem::create_directory("../bin/logs");
            std::ofstream file(ss.str(), std::ios::binary);
            file << Graphics::Utils::Log::GetLogStream().str();
        }

    }

    void GLAPIENTRY
        GLDebugMessageCallback(GLenum source,
            GLenum type,
            GLuint id,
            GLenum severity,
            GLsizei length,
            const GLchar* message,
            const void* userParam)
    {
        std::stringstream ss;
        ss << "OpenGL Debug Callback: " << type << " type=" << std::hex << type << ", severity=" << std::hex << severity << ", message: " << message;

        if (severity == GL_DEBUG_SEVERITY_NOTIFICATION)
            return;

        LOG_GL_ERROR(ss.str());
        WriteLogToFile(); // If we're in this code, we may have crashed the UI so we'll write the log to a file for debugging.

        APP_ASSERT(false, "Exiting due to OpenGL error");
    }

}