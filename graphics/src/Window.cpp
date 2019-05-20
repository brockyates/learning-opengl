#include "pch.h"
#include "Window.h"

#include "config/WindowConfig.h"
#include "events/EventDispatcher.h"
#include "logging/GLDebugMessageCallback.h"

namespace Graphics {

    WindowedSettings Window::InitializeWindowedSettings()
    {
        int width, height, xpos, ypos;

        glfwGetWindowSize(m_Window.get(), &width, &height);
        glfwGetWindowPos(m_Window.get(), &xpos, &ypos);

        return { width, height, xpos, ypos };
    }

    EventHandler<ChangeToWindowedEvent> Window::OnChangeToWindowed()
    {
        return [this](ChangeToWindowedEvent& event)
        {
            m_Properties.Mode = WindowMode::Windowed;
            glfwHideWindow(m_Window.get());
            glfwSetWindowMonitor(m_Window.get(), 0, 0, 0, m_WindowedSettings.Width, m_WindowedSettings.Height, GLFW_DONT_CARE);
            glfwSetWindowPos(m_Window.get(), m_WindowedSettings.Xpos, m_WindowedSettings.Ypos);
            glfwShowWindow(m_Window.get());
        };
    }

    EventHandler<ChangeToFullscreenEvent> Window::OnChangeToFullscreen()
    {
        return [this](ChangeToFullscreenEvent&)
        {
            m_Properties.Mode = WindowMode::Fullscreen;

            int width, height, xpos, ypos;

            glfwGetWindowSize(m_Window.get(), &width, &height);
            glfwGetWindowPos(m_Window.get(), &xpos, &ypos);

            m_WindowedSettings = { width, height, xpos, ypos };

            glfwSetWindowMonitor(m_Window.get(), glfwGetPrimaryMonitor(), 0, 0, m_Properties.Resolution.Width, m_Properties.Resolution.Height, GLFW_DONT_CARE);
            glfwShowWindow(m_Window.get());
            glfwFocusWindow(m_Window.get());
        };
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

    void Window::OnEvent(Event& event)
    {
        EventDispatcher dispatcher(event);

        dispatcher.Dispatch<ChangeToWindowedEvent>(OnChangeToWindowed());
        dispatcher.Dispatch<ChangeToFullscreenEvent>(OnChangeToFullscreen());
    }

}
