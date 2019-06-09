#pragma once

#include "IRenderer.h"
#include "RendererTypes.h"

namespace Graphics
{

    class TestRenderer final : public IRenderer
    {
    public:
        TestRenderer() = default;

        ProgramId CreateProgram() override;
    };

}