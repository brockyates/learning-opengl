#pragma once

#include "Window.h"

namespace Graphics {

    class ImGuiRenderer
    {
    public:
        explicit ImGuiRenderer(const Window& window);
        ~ImGuiRenderer();

        ImGuiRenderer(const ImGuiRenderer&) = default;
        ImGuiRenderer(ImGuiRenderer&&) = default;

        ImGuiRenderer& operator=(const ImGuiRenderer&) = delete;
        ImGuiRenderer& operator=(ImGuiRenderer&&) = delete;

        static void BeginFrame();
        void Render() const;

    private:
        const Window& window_;
    };

}
