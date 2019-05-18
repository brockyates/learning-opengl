#include "pch.h"
#include "Window.h"

#include "layers/Layer.h"
#include "logging/GLDebugMessageCallback.h"

namespace Graphics {

    Window::Window()
        : m_Context()
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

    void Window::OnUpdate()
    {
        glfwSwapBuffers(m_Context.NativeWindow());
        glfwPollEvents();
    }

}
