#include "pch.h"
#include "GLDebugMessageCallback.h"

#include "helpers/FileHelpers.h"
#include "helpers/GlobalMacros.h"

#include "Log.h"

#include <ctime>
#include <filesystem>
#include <sstream>

namespace Graphics
{
    namespace
    {
        void WriteLogToFile()
        {
            const auto t = std::time(nullptr);
            const auto utcTime = *std::gmtime(&t);

            std::stringstream ss;
            ss << "logs/GraphicsLog" << std::put_time(&utcTime, "%Y%m%d_%H%M%S") << ".txt";
            std::filesystem::create_directory("logs");

            WriteToFile(ss.str(), Utils::Log::GetLogStream().str());
        }
    }

    void GLAPIENTRY
        GlDebugMessageCallback(GLenum /*source*/,
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

        LogGlError(ss.str());
        WriteLogToFile(); // If we're in this code, we may have crashed the UI so we'll write the log to a file for debugging.

        AppAssert(false, "Exiting due to OpenGL error");
    }
}