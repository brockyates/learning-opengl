#include "pch.h"
#include "Window.h"

#include "config/WindowConfig.h"
#include "events/EventDispatcher.h"
#include "logging/GLDebugMessageCallback.h"

namespace Graphics {

    Window::Window()
        : m_Properties(WindowConfig::Properties)
        , m_Window(CreateInitialWindowedGLFWWindow(m_Properties))
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

    EventHandler<ChangeResolutionEvent> Window::OnResolutionChange()
    {
        return [this](const ChangeResolutionEvent& event)
        {
            m_Properties.Resolution = event.NewResolution();
        };
    }

    EventHandler<ChangeToWindowedEvent> Window::OnChangeToWindowed()
    {
        return [this](const ChangeToWindowedEvent& event)
        {
            m_Properties.Mode = WindowMode::Windowed;
            glfwHideWindow(m_Window.get());
            glfwSetWindowMonitor(m_Window.get(), 0, 0, 0, m_Properties.WindowedProperties.Width, m_Properties.WindowedProperties.Height, GLFW_DONT_CARE);
            glfwSetWindowPos(m_Window.get(), m_Properties.WindowedProperties.Xpos, m_Properties.WindowedProperties.Ypos);
            glfwShowWindow(m_Window.get());
        };
    }

    EventHandler<ChangeToFullscreenEvent> Window::OnChangeToFullscreen()
    {
        return [this](const ChangeToFullscreenEvent&)
        {
            m_Properties.Mode = WindowMode::Fullscreen;

            int width, height, xpos, ypos;

            glfwGetWindowSize(m_Window.get(), &width, &height);
            glfwGetWindowPos(m_Window.get(), &xpos, &ypos);

            m_Properties.WindowedProperties = { width, height, xpos, ypos };

            glfwSetWindowMonitor(m_Window.get(), glfwGetPrimaryMonitor(), 0, 0, m_Properties.Resolution.Width, m_Properties.Resolution.Height, GLFW_DONT_CARE);
            glfwShowWindow(m_Window.get());
            glfwFocusWindow(m_Window.get());
        };
    }

    EventHandler<WindowCloseEvent> Window::OnWindowClose()
    {
        return [this](const WindowCloseEvent& event)
        {
            glfwSetWindowShouldClose(m_Window.get(), GLFW_TRUE);
        };
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

    void Window::OnEvent(const Event& event)
    {
        EventDispatcher dispatcher(event);

        dispatcher.Dispatch<ChangeResolutionEvent>(OnResolutionChange());
        dispatcher.Dispatch<ChangeToWindowedEvent>(OnChangeToWindowed());
        dispatcher.Dispatch<ChangeToFullscreenEvent>(OnChangeToFullscreen());
        dispatcher.Dispatch<WindowCloseEvent>(OnWindowClose());
    }

}
