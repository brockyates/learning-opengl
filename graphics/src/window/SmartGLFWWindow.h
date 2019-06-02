#pragma once

#include <GLFW/glfw3.h>

#include <memory>

namespace Graphics {

    struct WindowProperties;

    struct DestroyGlfwWin {

        void operator()(GLFWwindow* ptr) const
        {
            glfwDestroyWindow(ptr);
        }
    };

    using SmartGlfwWindow = std::unique_ptr<GLFWwindow, DestroyGlfwWin>;

    SmartGlfwWindow CREATE_GLFW_WINDOW(WindowProperties& windowProperties);

}
