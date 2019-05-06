#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <memory>

namespace Graphics {

    struct DestroyGLFWWin {

        void operator()(GLFWwindow* ptr) {
            glfwDestroyWindow(ptr);
        }
    };

    using SmartGLFWWindow = std::unique_ptr<GLFWwindow, DestroyGLFWWin>;

    SmartGLFWWindow CreateGLFWWindow();

}
