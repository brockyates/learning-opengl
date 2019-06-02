#pragma once

#include <GLFW/glfw3.h>

#include <utility>

namespace Graphics {

    class WindowInput
    {
    public:
        explicit WindowInput(GLFWwindow* window);

        [[nodiscard]] bool IsKeyPressed(int keycode) const;
        [[nodiscard]] bool IsKeyReleased(int keycode) const;

        [[nodiscard]] bool IsMouseButtonPressed(int button) const;
        [[nodiscard]] std::pair<float, float> GetMousePosition() const;

    private:
        GLFWwindow* window_;
    };

}
