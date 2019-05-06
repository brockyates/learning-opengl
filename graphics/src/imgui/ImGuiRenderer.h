#pragma once
#include <GLFW/glfw3.h>

namespace Graphics {

    struct WindowProperties;

    class ImGuiRenderer
    {
    public:
        ImGuiRenderer(GLFWwindow * window);
        ~ImGuiRenderer();

        void BeginFrame() const;
        void Render(const WindowProperties& windowProperties) const;
    };

}
