#include "pch.h"
#include "Window.h"

#include "config/WindowConfig.h"
#include "logging/GLDebugMessageCallback.h"

namespace Graphics {

    WindowedSettings Window::InitializeWindowedSettings()
    {
        int width, height, xpos, ypos;

        glfwGetWindowSize(m_Window.get(), &width, &height);
        glfwGetWindowPos(m_Window.get(), &xpos, &ypos);

        return { width, height, xpos, ypos };
    }

    Window::Window()
        : m_Properties(WindowConfig::Properties)
        , m_Window(CreateInitialWindowedGLFWWindow(m_Properties))
        , m_WindowedSettings(InitializeWindowedSettings())
        , Input(m_Window.get())
    {
#ifdef APP_DEBUG
        glEnable(GL_DEBUG_OUTPUT);
        glDebugMessageCallback(GLDebugMessageCallback, 0);
#endif
    }

    Window::~Window()
    {
        glfwTerminate();
    }

    bool Window::ShouldClose()
    {
        return glfwWindowShouldClose(m_Window.get());
    }

    bool Window::IsFullscreen() const
    {
        return m_Properties.Mode == WindowMode::Fullscreen;
    }

    void Window::Update()
    {
        glfwSwapBuffers(m_Window.get());
        glfwPollEvents();
    }

}
