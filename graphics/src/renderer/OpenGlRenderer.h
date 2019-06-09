#pragma once

#include "IRenderer.h"
#include "RendererTypes.h"

namespace Graphics
{
    class OpenGlRenderer final : public IRenderer
    {
    public:
        Program CreateProgram() override;
    };
}
