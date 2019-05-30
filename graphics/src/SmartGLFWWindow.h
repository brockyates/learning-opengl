#pragma once

#include <GLFW/glfw3.h>

#include <memory>

namespace graphics {

    struct WindowProperties;

    struct DestroyGLFWWin {

        void operator()(GLFWwindow* ptr) {
            glfwDestroyWindow(ptr);
        }
    };

    using SmartGLFWWindow = std::unique_ptr<GLFWwindow, DestroyGLFWWin>;

    SmartGLFWWindow CreateGLFWWindow(WindowProperties& windowProperties);

}
