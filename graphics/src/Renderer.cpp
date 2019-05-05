#include "pch.h"
#include "Renderer.h"

namespace Graphics {

    void GLClearError()
    {
        while (glGetError() != GL_NO_ERROR);
    }

    bool GLLogCallError(const char* function, const char* file, int line)
    {
        while (GLenum error = glGetError())
        {
            std::stringstream ss;
            ss << "OpenGL Error: " << error << " in " << function << " at " << file << ":" << line;
            LOG_GL_ERROR(ss.str());
            return false;
        }

        return true;
    }

    void GLLogCall(const char* function, const char* file, int line)
    {
            std::stringstream ss;
            ss << function << " at " << file << ":" << line;
            LOG_GL_DEBUG(ss.str());
    }

}
