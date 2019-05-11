#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <memory>

namespace Graphics {

    struct WindowProperties;

    struct DestroyGLFWWin {

        void operator()(GLFWwindow* ptr) {
            glfwDestroyWindow(ptr);
        }
    };

    using SmartGLFWWindow = std::unique_ptr<GLFWwindow, DestroyGLFWWin>;

    SmartGLFWWindow CreateWindowedGLFWWindow(WindowProperties& windowProperties);
    SmartGLFWWindow CreateFullscreenGLFWWindow(WindowProperties& windowProperties);

}
