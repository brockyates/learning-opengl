#pragma once
#include <GLFW/glfw3.h>

namespace Graphics {

    class ImGuiRenderer
    {
    public:
        ImGuiRenderer(GLFWwindow* window);
        ~ImGuiRenderer();

        static void BeginFrame();
        static void Render(unsigned int height, unsigned int width);
    };

}
