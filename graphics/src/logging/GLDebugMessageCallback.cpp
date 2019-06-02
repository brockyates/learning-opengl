#include "pch.h"
#include "GLDebugMessageCallback.h"

#include "GlobalMacros.h"
#include "Log.h"

#include <ctime>
#include <filesystem>
#include <fstream>
#include <sstream>

namespace Graphics {

    namespace {

        void WRITE_LOG_TO_FILE()
        {
            const auto t = std::time(nullptr);
            const auto utcTime = *std::gmtime(&t);

            std::stringstream ss;
            ss << "../bin/logs/GraphicsLog" << std::put_time(&utcTime, "%Y%m%d_%H%M%S") << ".txt";

            std::filesystem::create_directory("../bin/logs");
            std::ofstream file(ss.str(), std::ios::binary);
            file << Utils::Log::GetLogStream().str();
        }

    }

    void GLAPIENTRY
        GL_DEBUG_MESSAGE_CALLBACK(GLenum /*source*/,
                                  const GLenum type,
                               GLuint /*id*/,
                                  const GLenum severity,
                               GLsizei /*length*/,
                               const GLchar* message,
                               const void* /*userParam*/)
    {
        std::stringstream ss;
        ss << "OpenGL Debug Callback: " << type << " type=" << std::hex << type << ", severity=" << std::hex << severity << ", message: " << message;

        if (severity == GL_DEBUG_SEVERITY_NOTIFICATION)
            return;

        LOG_GL_ERROR(ss.str());
        WRITE_LOG_TO_FILE(); // If we're in this code, we may have crashed the UI so we'll write the log to a file for debugging.

        APP_ASSERT(false, "Exiting due to OpenGL error");
    }

}