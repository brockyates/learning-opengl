#pragma once

#include <GLFW/glfw3.h>

namespace Graphics {

    class Input
    {
    public:
        Input(GLFWwindow* window);

        Input(Input&&) = default;
        Input& operator=(Input&&) = default;

        bool IsKeyPressed(int keycode);

        bool IsMouseButtonPressed(int button);
        std::pair<float, float> GetMousePosition();

    private:
        GLFWwindow* m_Window;
    };

}
