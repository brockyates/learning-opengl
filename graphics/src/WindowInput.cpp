#include "pch.h"
#include "WindowInput.h"

namespace Graphics {

    WindowInput::WindowInput(GLFWwindow* window)
        : window_(window)
    {}

    bool WindowInput::IsKeyPressed(int keycode) const
    {
        const auto keyboardState = glfwGetKey(window_, keycode);
        return keyboardState == GLFW_PRESS || keyboardState == GLFW_REPEAT;
    }

    bool WindowInput::IsKeyReleased(int keycode) const
    {
        const auto keyboardState = glfwGetKey(window_, keycode);
        return keyboardState == GLFW_RELEASE;
    }

    bool WindowInput::IsMouseButtonPressed(int button) const
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
