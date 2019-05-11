#include "pch.h"
#include "Window.h"
#include "config/WindowConfig.h"

#include "logging/GLDebugMessageCallback.h"
#include "layers/Layer.h"

namespace Graphics {

    Window::Window()
        : m_WindowProperties(WindowConfig::Properties)
        , m_Window(CreateWindowedGLFWWindow(m_WindowProperties))
        , m_UIRenderer(ImGuiRenderer(m_Window.get()))
        , m_Layers(m_WindowProperties, m_Window.get())
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

    void Window::SetWindowFullscreenState()
    {
        if (m_IsFullscreen && !m_Layers.UIIsEnabled())
            return;

        if (!m_IsFullscreen && m_Layers.UIIsEnabled())
            return;

        if (m_IsFullscreen && m_Layers.UIIsEnabled())
        {
            m_UIRenderer.Shutdown();
            glfwTerminate();
            m_Window.reset();
            m_WindowProperties.IsFullscreen = false;
            m_Window = CreateWindowedGLFWWindow(m_WindowProperties);
            m_UIRenderer = ImGuiRenderer(m_Window.get());
            m_Layers.SetWindow(m_Window.get());
            m_IsFullscreen = false;

            return;
        }

        m_UIRenderer.Shutdown();
        glfwTerminate();
        m_Window.reset();
        m_WindowProperties.IsFullscreen = true;
        m_Window = CreateFullscreenGLFWWindow(m_WindowProperties);
        m_UIRenderer = ImGuiRenderer(m_Window.get());
        m_Layers.SetWindow(m_Window.get());
        m_IsFullscreen = true;
    }

    void Window::OnUpdate()
    {
        SetWindowFullscreenState();

        DrawScene();

        if (!m_IsFullscreen)
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

        if (m_Layers.UIIsEnabled())
        {
            m_Layers.OnImGuiRender();
        }

        m_UIRenderer.Render(m_WindowProperties);

    }

}
