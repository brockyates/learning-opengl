#pragma once

#include <GLFW/glfw3.h>

namespace Graphics {

    class WindowInput
    {
    public:
        WindowInput(GLFWwindow* window);

        WindowInput(WindowInput&&) = default;
        WindowInput& operator=(WindowInput&&) = default;

        bool IsKeyPressed(int keycode);

        bool IsMouseButtonPressed(int button);
        std::pair<float, float> GetMousePosition();

    private:
        GLFWwindow* m_Window;
    };

}
