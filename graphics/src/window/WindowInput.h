#pragma once

#include <GLFW/glfw3.h>

#include <utility>

namespace Graphics
{
    class WindowInput
    {
    public:
        explicit WindowInput(GLFWwindow* window);

        [[nodiscard]] bool IsKeyPressed(int32_t keycode) const;
        [[nodiscard]] bool IsKeyReleased(int32_t keycode) const;

        [[nodiscard]] bool IsMouseButtonPressed(int32_t button) const;
        [[nodiscard]] std::pair<float, float> GetMousePosition() const;

    private:
        GLFWwindow* window_;
    };
}
