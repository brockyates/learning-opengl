#include "pch.h"
#include "Renderer.h"

#include "Log.h"
#include <sstream>

namespace App {

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

    Renderer::Renderer()
    {
        LOG_TRACE("Entering Renderer()");
        LOG_DEBUG("Renderer created");
        LOG_TRACE("Exiting Renderer()");
    }

    Renderer::~Renderer()
    {
        LOG_TRACE("Entering ~Renderer()");
        LOG_DEBUG("Renderer deleted");
        LOG_TRACE("Exiting ~Renderer()");
    }

}
