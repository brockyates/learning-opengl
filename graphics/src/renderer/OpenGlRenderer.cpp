#include "pch.h"
#include "OpenGlRenderer.h"

#include <glad/glad.h>

namespace Graphics
{
    ProgramId OpenGlRenderer::CreateProgram()
    {
        return ProgramId{ glCreateProgram() };
    }

}
