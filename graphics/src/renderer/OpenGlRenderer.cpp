#include "pch.h"
#include "OpenGlRenderer.h"

#include <glad/glad.h>

namespace Graphics
{
    Program OpenGlRenderer::CreateProgram()
    {
        return Program{ glCreateProgram() };
    }

}
