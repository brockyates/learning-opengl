#include "pch.h"
#include "Window.h"

#include "layers/Layer.h"
#include "logging/GLDebugMessageCallback.h"

namespace Graphics {

    Window::Window()
        : m_Context()
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
        glfwTerminate();
    }

    void Window::OnUpdate()
    {
        DrawScene();

        if (!(m_Context.Properties.Mode == WindowMode::Fullscreen))
        {
            DrawUIElements();
        }

        glfwSwapBuffers(m_Context.NativeWindow());
        glfwPollEvents();
    }

    bool Window::ShouldClose()
    {
        return glfwWindowShouldClose(m_Context.NativeWindow()) || m_LayerManager.WindowShouldClose();
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
