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

    void Window::SetNextWindowMode()
    {
        if ((m_WindowProperties.Mode == WindowMode::Fullscreen) && (m_Layers.NextWindowMode() == WindowMode::Fullscreen))
            return;

        if ((m_WindowProperties.Mode == WindowMode::Windowed) && (m_Layers.NextWindowMode() == WindowMode::Windowed))
            return;

        if ((m_WindowProperties.Mode == WindowMode::Fullscreen) && (m_Layers.NextWindowMode() == WindowMode::Windowed))
        {
            //Switch from Fullscreen to Windowed
            m_UIRenderer.Shutdown();
            glfwTerminate();
            m_Window.reset();
            m_WindowProperties.Mode = WindowMode::Windowed;
            m_Window = CreateWindowedGLFWWindow(m_WindowProperties);
            m_UIRenderer = ImGuiRenderer(m_Window.get());
            m_Layers.OnWindowStateChange(m_Window.get());

            return;
        }

        //Switch from Windowed to Fullscreen
        m_UIRenderer.Shutdown();
        glfwTerminate();
        m_Window.reset();
        m_WindowProperties.Mode = WindowMode::Fullscreen;
        m_Window = CreateFullscreenGLFWWindow(m_WindowProperties);
        m_UIRenderer = ImGuiRenderer(m_Window.get());
        m_Layers.OnWindowStateChange(m_Window.get());
    }

    void Window::OnUpdate()
    {
        SetNextWindowMode();

        DrawScene();

        if (!(m_WindowProperties.Mode == WindowMode::Fullscreen))
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
        m_UIRenderer.Render(m_WindowProperties);

    }

}
