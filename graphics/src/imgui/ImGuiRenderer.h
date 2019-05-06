#pragma once
#include <GLFW/glfw3.h>

namespace Graphics {

    struct WindowProperties;

    class ImGuiRenderer
    {
    public:
        ImGuiRenderer(GLFWwindow * window);
        ~ImGuiRenderer();

        ImGuiRenderer(ImGuiRenderer&) = delete;
        ImGuiRenderer& operator=(ImGuiRenderer&) = delete;

        void BeginFrame() const;
        void Render(const WindowProperties& windowProperties) const;
    };

}
