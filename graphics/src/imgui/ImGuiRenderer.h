#pragma once

#include "Window.h"

namespace Graphics {

    struct WindowProperties;

    class ImGuiRenderer
    {
    public:
        ImGuiRenderer(WindowContext* context);
        ~ImGuiRenderer();

        ImGuiRenderer(ImGuiRenderer&) = default;
        ImGuiRenderer& operator=(ImGuiRenderer&) = default;

        void BeginFrame() const;
        void Render(Window* window);
    };

}
