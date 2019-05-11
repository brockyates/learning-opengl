#pragma once

#include <GLFW/glfw3.h>

namespace Graphics {

    class Input
    {
    public:
        Input(GLFWwindow* window);

        Input(Input&) = delete;
        Input(Input&&) = delete;
        Input& operator=(Input&) = delete;
        Input& operator=(Input&&) = delete;

        bool IsKeyPressed(int keycode);

        bool IsMouseButtonPressed(int button);
        std::pair<float, float> GetMousePosition();

    private:
        GLFWwindow* m_Window;
    };

}
