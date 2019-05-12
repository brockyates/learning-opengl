#include "pch.h"
#include "Window.h"
#include "config/WindowConfig.h"

#include "SmartGLFWWindow.h"

#include "logging/GLDebugMessageCallback.h"
#include "layers/Layer.h"

namespace Graphics {

    Window::Window()
        : m_Window(CreateWindowedGLFWWindow(WindowConfig::Properties))
        , m_WindowContext(std::make_unique<WindowContext>(m_Window.get(), WindowConfig::Properties))
        , m_UIRenderer(ImGuiRenderer(m_Window.get()))
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
            ShutdownCurrentContext();
            m_WindowContext->Properties = m_Layers.NextWindowProperties();

            if(m_Layers.NextWindowProperties().Mode == WindowMode::Windowed)
            {                
                m_Window = CreateWindowedGLFWWindow(m_WindowContext->Properties);
            }
            else
            {
                m_Window = CreateFullscreenGLFWWindow(m_WindowContext->Properties);
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

    void Window::ShutdownCurrentContext()
    {
        m_UIRenderer.Shutdown();
        glfwTerminate();
        m_Window.reset(); //The existing GLFW window needs to be destroyed before the new window is constructed
    }

    void Window::StartWindowSystems()
    {
        const auto windowProperties = m_WindowContext->Properties;
        m_WindowContext = std::make_unique<WindowContext>(m_Window.get(), windowProperties);

        m_UIRenderer = ImGuiRenderer(m_Window.get());
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
