#include "pch.h"
#include "SmartGLFWWindow.h"

#include "config/WindowDefaults.h"
#include "WindowProperties.h"

namespace Graphics {

    void InitializeGLFW()
    {
        auto glfwInitStatus = glfwInit();
        APP_ASSERT(glfwInitStatus, "Failed to initialize GLFW");

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_MAXIMIZED, GL_FALSE);
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

            // We only need to maintain window properties in Windowed mode
            if (windowProperties.Mode == WindowMode::Fullscreen)
                return;

            windowProperties.Layout.Width = width;
            windowProperties.Layout.Height = height;
        });

        LOG_GL_INFO(glGetString(GL_RENDERER));
        LOG_GL_INFO(glGetString(GL_VERSION));
    } 

    namespace {

        ResolutionSetting GetDesktopResolutionOrDefault()
        {
            const auto videoMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
            const auto foundSupportedResolution = std::find_if(std::begin(WindowDefaults::SupportedResolutions), std::end(WindowDefaults::SupportedResolutions), [videoMode](const ResolutionSetting& setting)
            {
                return setting.Width == videoMode->width;
            });

            if(foundSupportedResolution != std::end(WindowDefaults::SupportedResolutions))
                return *foundSupportedResolution;

            const auto defaultResolution = WindowDefaults::SupportedResolutions[3]; // 720p as a safe default resolution.
            return defaultResolution;
        }

    }

    // Create a windowed GLFW window, half the size of desktop resolution, centered on screen.
    // If the desktop resolution isn't supported, we'll choose 720p as the default window size.
    SmartGLFWWindow CreateGLFWWindow(WindowProperties& windowProperties)
    {
        InitializeGLFW();
        windowProperties.Resolution = GetDesktopResolutionOrDefault();

        windowProperties.Layout = WindowLayout(
            windowProperties.Resolution.Width / 2,
            windowProperties.Resolution.Height / 2,
            windowProperties.Resolution.Width / 4,
            windowProperties.Resolution.Height / 4,
            static_cast<float>(windowProperties.Resolution.Width) / static_cast<float>(windowProperties.Resolution.Height));

        glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

        auto window = SmartGLFWWindow(glfwCreateWindow(windowProperties.Layout.Width, windowProperties.Layout.Height, windowProperties.Title.c_str(), NULL, NULL));
        glfwSetWindowPos(window.get(), windowProperties.Layout.Xpos, windowProperties.Layout.Ypos);
        glfwShowWindow(window.get());

        SetWindowContext(window.get(), windowProperties);
        return window;
    }

}
