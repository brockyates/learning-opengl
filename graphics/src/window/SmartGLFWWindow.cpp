#include "pch.h"
#include "SmartGLFWWindow.h"

#include "window/WindowDefaults.h"
#include "logging/Log.h"

#include "helpers/GlobalMacros.h"
#include "WindowProperties.h"

#include <glad/glad.h>

namespace Graphics
{
    void InitializeGlfw()
    {
        const auto glfwInitStatus = glfwInit();
        AppAssert(glfwInitStatus, "Failed to initialize GLFW");

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_MAXIMIZED, GL_FALSE);
    }

    void SetWindowContext(GLFWwindow* window, WindowProperties& windowProperties)
    {
        if (!window)
        {
            glfwTerminate();
            AppAssert(window, "Failed to create GLFW window");
        }

        glfwMakeContextCurrent(window);
        glfwSwapInterval(1);
        const auto gladLoadStatus = gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
        if (!gladLoadStatus)
        {
            glfwTerminate();
            AppAssert(gladLoadStatus, "Failed to initialize Glad");
        }

        glfwSetWindowUserPointer(window, &windowProperties);

        // Set GLFW callbacks
        glfwSetWindowSizeCallback(window, [](GLFWwindow* window, const int32_t width, const int32_t height)
        {
            auto& windowProperties = *static_cast<WindowProperties*>(glfwGetWindowUserPointer(window));

            // We only need to maintain window properties in Windowed mode
            if (windowProperties.Mode == WindowMode::Fullscreen)
                return;

            windowProperties.Layout.Width = width;
            windowProperties.Layout.Height = height;
        });

        LogGlInfo(glGetString(GL_RENDERER));
        LogGlInfo(glGetString(GL_VERSION));
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
    SmartGlfwWindow CreateGlfwWindow(WindowProperties& windowProperties)
    {
        InitializeGlfw();
        windowProperties.Resolution = GetDesktopResolutionOrDefault();

        windowProperties.Layout = WindowLayout(
            windowProperties.Resolution.Width / 2,
            windowProperties.Resolution.Height / 2,
            windowProperties.Resolution.Width / 4,
            windowProperties.Resolution.Height / 4,
            static_cast<float>(windowProperties.Resolution.Width) / static_cast<float>(windowProperties.Resolution.Height));

        glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

        auto window = SmartGlfwWindow(glfwCreateWindow(windowProperties.Layout.Width, windowProperties.Layout.Height, windowProperties.Title.c_str(), nullptr, nullptr));
        glfwSetWindowPos(window.get(), windowProperties.Layout.XPos, windowProperties.Layout.YPos);
        glfwShowWindow(window.get());

        SetWindowContext(window.get(), windowProperties);
        return window;
    }
}
