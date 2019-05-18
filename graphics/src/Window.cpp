#include "pch.h"
#include "Window.h"

#include "logging/GLDebugMessageCallback.h"

namespace Graphics {

    WindowedSettings Window::InitializeWindowedSettings()
    {
        int width, height, xpos, ypos;

        glfwGetWindowSize(m_Context.NativeWindow(), &width, &height);
        glfwGetWindowPos(m_Context.NativeWindow(), &xpos, &ypos);

        return { width, height, xpos, ypos };
    }

    Window::Window()
        : m_Context()
        , m_WindowedSettings(InitializeWindowedSettings())
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
        return glfwWindowShouldClose(m_Context.NativeWindow());
    }

    bool Window::IsFullscreen() const
    {
        return m_Context.Properties.Mode == WindowMode::Fullscreen;
    }

    void Window::Update()
    {
        glfwSwapBuffers(m_Context.NativeWindow());
        glfwPollEvents();
    }

}
