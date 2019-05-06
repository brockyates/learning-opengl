#include "pch.h"
#include "SmartGLFWWindow.h"

namespace Graphics {

    SmartGLFWWindow CreateGLFWWindow()
    {
        bool glfwInitStatus = glfwInit();
        APP_ASSERT(glfwInitStatus, "Failed to initialize GLFW");

        auto window = SmartGLFWWindow(glfwCreateWindow(1920, 1080, "Hello World", NULL, NULL));
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
