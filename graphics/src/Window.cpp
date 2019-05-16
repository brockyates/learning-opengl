#include "pch.h"
#include "Window.h"
#include "config/WindowConfig.h"

#include "SmartGLFWWindow.h"

#include "logging/GLDebugMessageCallback.h"
#include "layers/Layer.h"

namespace Graphics {

    Window::Window()
        : m_Window(CreateInitialWindowedGLFWWindow(WindowConfig::Properties))
        , m_WindowContext(std::make_unique<WindowContext>(m_Window.get(), WindowConfig::Properties))
        , m_UIRenderer(ImGuiRenderer(m_WindowContext.get()))
        , m_Layers(m_WindowContext.get())
    {
#ifdef APP_DEBUG
        glEnable(GL_DEBUG_OUTPUT);
        glDebugMessageCallback(GLDebugMessageCallback, 0);
#endif
    }

    Window::~Window()
    {
        m_UIRenderer.Shutdown();
    }

    void Window::SetNextWindowMode()
    {
        if (m_Layers.IsNewWindWindowRequired())
        {
            m_WindowContext->Properties = m_Layers.NextWindowProperties();

            if(m_Layers.NextWindowProperties().Mode == WindowMode::Windowed)
            {
                glfwSetWindowMonitor(m_Window.get(), 0, 0, 0, m_WindowContext->Properties.Resolution.Width, m_WindowContext->Properties.Resolution.Height, GLFW_DONT_CARE);
            }
            else
            {
                glfwSetWindowMonitor(m_Window.get(), glfwGetPrimaryMonitor(), 0, 0, m_WindowContext->Properties.Resolution.Width, m_WindowContext->Properties.Resolution.Height, GLFW_DONT_CARE);
                glfwShowWindow(m_Window.get());
                glfwFocusWindow(m_Window.get());
            }

            StartWindowSystems();

            return;
        }

        if (m_Layers.IsResolutionChangeRequired())
        {
            m_WindowContext->Properties = m_Layers.NextWindowProperties();

            glfwSetWindowSize(m_Window.get(),
                m_WindowContext->Properties.Resolution.Width,
                m_WindowContext->Properties.Resolution.Height);

            m_Layers.OnWindowStateChange(m_WindowContext.get());

            return;
        }
    }

    void Window::StartWindowSystems()
    {
        m_Layers.OnWindowStateChange(m_WindowContext.get());
    }

    void Window::OnUpdate()
    {
        SetNextWindowMode();

        DrawScene();

        if (!(m_WindowContext->Properties.Mode == WindowMode::Fullscreen))
        {
            DrawUIElements();
        }

        glfwSwapBuffers(m_Window.get());
        glfwPollEvents();
    }

    bool Window::ShouldClose() const
    {
        return glfwWindowShouldClose(m_Window.get()) || m_Layers.WindowShouldClose();
    }

    void Window::DrawScene()
    {
        m_Layers.OnUpdate();
    }

    void Window::DrawUIElements()
    {
        m_UIRenderer.BeginFrame();
        m_Layers.OnImGuiRender();
        m_UIRenderer.Render(m_WindowContext->Properties);
    }

}
