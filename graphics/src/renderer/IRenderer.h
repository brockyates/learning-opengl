#pragma once

#include "RendererTypes.h"

namespace Graphics
{
    class IRenderer
    {
    public:
        IRenderer() = default;
        virtual ~IRenderer() = default;

        IRenderer(const IRenderer&) = default;
        IRenderer(IRenderer&&) = default;
        IRenderer& operator=(const IRenderer&) = default;
        IRenderer& operator=(IRenderer&&) = default;

        virtual ProgramId CreateProgram() = 0;
    };

}
