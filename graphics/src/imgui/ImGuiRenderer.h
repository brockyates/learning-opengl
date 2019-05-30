#pragma once

#include "Window.h"

namespace graphics {

    class ImGuiRenderer
    {
    public:
        ImGuiRenderer(const Window& window);
        ~ImGuiRenderer();

        ImGuiRenderer(ImGuiRenderer&) = default;
        ImGuiRenderer& operator=(ImGuiRenderer&) = default;

        void BeginFrame() const;
        void Render();

    private:
        const Window& m_Window;
    };

}
