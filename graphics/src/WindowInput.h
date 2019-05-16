#pragma once

#include <GLFW/glfw3.h>

namespace Graphics {

    class WindowInput
    {
    public:
        WindowInput(GLFWwindow* window);

        WindowInput(WindowInput&&) = default;
        WindowInput& operator=(WindowInput&&) = default;

        bool IsKeyPressed(int keycode) const;
        bool IsKeyReleased(int keycode) const;

        bool IsMouseButtonPressed(int button) const;
        std::pair<float, float> GetMousePosition() const;

    private:
        GLFWwindow* m_Window;
    };

}
