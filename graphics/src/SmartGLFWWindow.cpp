#include "pch.h"
#include "SmartGLFWWindow.h"
#include "WindowProperties.h"

namespace Graphics {

    SmartGLFWWindow CreateGLFWWindow(const WindowProperties& windowProperties)
    {
        auto glfwInitStatus = glfwInit();
        APP_ASSERT(glfwInitStatus, "Failed to initialize GLFW");

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        auto window = SmartGLFWWindow(glfwCreateWindow(windowProperties.Width, windowProperties.Height, windowProperties.Title.c_str(), NULL, NULL));
        if (!window)
        {
            glfwTerminate();
            APP_ASSERT(window, "Failed to create GLFW window");
        }

        glfwMakeContextCurrent(window.get());
        glfwSwapInterval(1);
        int gladLoadStatus = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        if (!gladLoadStatus)
        {
            glfwTerminate();
            APP_ASSERT(gladLoadStatus, "Failed to initialize Glad");
        }

        LOG_GL_INFO(glGetString(GL_RENDERER));
        LOG_GL_INFO(glGetString(GL_VERSION));
        return window;
    }

}
