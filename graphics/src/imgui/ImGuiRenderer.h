#pragma once
#include <GLFW/glfw3.h>

namespace Graphics {

    struct WindowProperties;

    class ImGuiRenderer
    {
    public:
        ImGuiRenderer(GLFWwindow * window);
        void Shutdown();

        ImGuiRenderer(ImGuiRenderer&) = default;
        ImGuiRenderer& operator=(ImGuiRenderer&) = default;

        void BeginFrame() const;
        void Render(const WindowProperties& windowProperties) const;
    };

}
