#include "pch.h"
#include "WindowInput.h"

namespace Graphics
{
    WindowInput::WindowInput(GLFWwindow* window)
        : window_(window)
    {}

    bool WindowInput::IsKeyPressed(const int32_t keycode) const
    {
        const auto keyboardState = glfwGetKey(window_, keycode);
        return keyboardState == GLFW_PRESS || keyboardState == GLFW_REPEAT;
    }

    bool WindowInput::IsKeyReleased(const int32_t keycode) const
    {
        const auto keyboardState = glfwGetKey(window_, keycode);
        return keyboardState == GLFW_RELEASE;
    }

    bool WindowInput::IsMouseButtonPressed(const int32_t button) const
    {
        const auto mouseState = glfwGetMouseButton(window_, button);
        return mouseState == GLFW_PRESS;
    }

    std::pair<float, float> WindowInput::GetMousePosition() const
    {
        double mousePositionX;
        double mousePositionY;

        glfwGetCursorPos(window_, &mousePositionX, &mousePositionY);
        return { static_cast<float>(mousePositionX), static_cast<float>(mousePositionY) };
    }
}
