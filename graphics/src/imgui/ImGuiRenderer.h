#pragma once

#include "WindowContext.h"

namespace Graphics {

    struct WindowProperties;

    class ImGuiRenderer
    {
    public:
        ImGuiRenderer(WindowContext* context);
        void Shutdown();

        ImGuiRenderer(ImGuiRenderer&) = default;
        ImGuiRenderer& operator=(ImGuiRenderer&) = default;

        void BeginFrame() const;
        void Render(const WindowProperties& windowProperties) const;
    };

}
