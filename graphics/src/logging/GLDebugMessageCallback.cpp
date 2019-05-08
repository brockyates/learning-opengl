#include "pch.h"
#include "GLDebugMessageCallback.h"

namespace Graphics {

    namespace {

        void FlushLogToFile()
        {
            std::time_t t = std::time(nullptr);
            std::tm utcTime = *std::gmtime(&t);

            std::stringstream ss;
            ss << "../bin/logs/GraphicsLog" << std::put_time(&utcTime, "%Y%m%d_%H%M%S") << ".txt";

            std::filesystem::create_directory("../bin/logs");
            std::ofstream file(ss.str(), std::ios::binary);
            file << Graphics::Utils::Log::GetLogStream().str();
            file.close();
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

        LOG_ERROR(ss.str());
        FlushLogToFile(); // If we're in this code, chances are the UI has crashed so we'll dump the log to a file for debugging.

        APP_ASSERT(false, "Exiting due to OpenGL error");
    }

}