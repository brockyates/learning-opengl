#include "pch.h"
#include "Window.h"

#include "config/WindowConfig.h"
#include "SmartGLFWWindow.h"
#include "layers/Layer.h"
#include "logging/GLDebugMessageCallback.h"

namespace Graphics {

    Window::Window()
        : m_Window(CreateInitialWindowedGLFWWindow(WindowConfig::Properties))
        , m_Context(m_Window.get(), WindowConfig::Properties)
        , m_UIRenderer(ImGuiRenderer(&m_Context))
        , m_LayerManager(&m_Context)
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

    void Window::OnUpdate()
    {
        DrawScene();

        if (!(m_Context.Properties.Mode == WindowMode::Fullscreen))
        {
            DrawUIElements();
        }

        glfwSwapBuffers(m_Window.get());
        glfwPollEvents();
    }

    bool Window::ShouldClose() const
    {
        return glfwWindowShouldClose(m_Window.get()) || m_LayerManager.WindowShouldClose();
    }

    void Window::DrawScene()
    {
        m_LayerManager.OnUpdate();
    }

    void Window::DrawUIElements()
    {
        m_UIRenderer.BeginFrame();
        m_LayerManager.OnImGuiRender();
        m_UIRenderer.Render(m_Context.Properties);
    }

}
