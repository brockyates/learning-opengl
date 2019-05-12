#include "pch.h"
#include "WindowInput.h"

namespace Graphics {

    WindowInput::WindowInput(GLFWwindow* window)
        : m_Window(window)
    {}

    bool WindowInput::IsKeyPressed(int keycode)
    {
        const auto keyboardState = glfwGetKey(m_Window, keycode);
        return keyboardState == GLFW_PRESS || keyboardState == GLFW_REPEAT;
    }

    bool WindowInput::IsMouseButtonPressed(int button)
    {
        const auto mouseState = glfwGetMouseButton(m_Window, button);
        return mouseState == GLFW_PRESS;
    }

    std::pair<float, float> WindowInput::GetMousePosition()
    {
        double mousePositionX;
        double mousePositionY;

        glfwGetCursorPos(m_Window, &mousePositionX, &mousePositionY);
        return { static_cast<float>(mousePositionX), static_cast<float>(mousePositionY) };
    }

}
