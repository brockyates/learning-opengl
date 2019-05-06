#include "pch.h"
#include "SmartGLFWWindow.h"
#include "WindowProperties.h"

namespace Graphics {

    SmartGLFWWindow CreateGLFWWindow(const WindowProperties& windowProperties)
    {
        bool glfwInitStatus = glfwInit();
        APP_ASSERT(glfwInitStatus, "Failed to initialize GLFW");

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

        LOG_GL_INFO(glGetString(GL_VERSION));
        return window;
    }

}
