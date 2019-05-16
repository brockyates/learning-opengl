#include "pch.h"
#include "SmartGLFWWindow.h"

#include "config/WindowConfig.h"
#include "WindowProperties.h"

namespace Graphics {

    void InitializeGLFW()
    {
        auto glfwInitStatus = glfwInit();
        APP_ASSERT(glfwInitStatus, "Failed to initialize GLFW");

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_MAXIMIZED, GL_TRUE);
        //glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    }

    void SetWindowContext(GLFWwindow* window, WindowProperties& windowProperties)
    {
        if (!window)
        {
            glfwTerminate();
            APP_ASSERT(window, "Failed to create GLFW window");
        }

        glfwMakeContextCurrent(window);
        glfwSwapInterval(1);
        int gladLoadStatus = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        if (!gladLoadStatus)
        {
            glfwTerminate();
            APP_ASSERT(gladLoadStatus, "Failed to initialize Glad");
        }

        glfwSetWindowUserPointer(window, &windowProperties);

        // Set GLFW callbacks
        glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height)
        {
            WindowProperties& windowProperties = *(WindowProperties*)glfwGetWindowUserPointer(window);

            windowProperties.Resolution.Width = width;
            windowProperties.Resolution.Height = height;
        });

        LOG_GL_INFO(glGetString(GL_RENDERER));
        LOG_GL_INFO(glGetString(GL_VERSION));
    } 

    namespace {

        ResolutionSetting GetDesktopResolutionOrDefault()
        {
            const auto mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
            const auto found = std::find_if(std::begin(WindowConfig::SupportedResolutions), std::end(WindowConfig::SupportedResolutions), [mode](const ResolutionSetting& setting)
            {
                return setting.Width == mode->width;
            });

            if(found != std::end(WindowConfig::SupportedResolutions))
                return *found;

            const auto defaultResolution = WindowConfig::SupportedResolutions[3]; // 720p as a safe default resolution.
            return defaultResolution;
        }

    }

    // Create a windowed GLFW window, half the size of desktop resolution, centered on screen.
    // If the desktop resolution isn't supported, we'll choose 720p as the default window size.
    SmartGLFWWindow CreateInitialWindowedGLFWWindow(WindowProperties& windowProperties)
    {
        InitializeGLFW();
        windowProperties.Resolution = GetDesktopResolutionOrDefault();

        glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
        auto window = SmartGLFWWindow(glfwCreateWindow(windowProperties.Resolution.Width / 2, windowProperties.Resolution.Height / 2, windowProperties.Title.c_str(), NULL, NULL));
        glfwSetWindowPos(window.get(), windowProperties.Resolution.Width / 4, windowProperties.Resolution.Height / 4);
        glfwShowWindow(window.get());

        SetWindowContext(window.get(), windowProperties);
        return window;
    }

}
