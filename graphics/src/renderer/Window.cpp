#include "pch.h"
#include "Window.h"

#include "logging/GLDebugMessageCallback.h"
#include "layers/Layer.h"

namespace Graphics {

    Window::Window()
        : m_WindowProperties("OpenGL Graphics Demo", 1920, 1080)
        , m_Window(CreateGLFWWindow(m_WindowProperties))
        , m_UIRenderer(ImGuiRenderer(m_Window.get()))
        , m_Layers(m_Window.get())
    {
#ifdef APP_DEBUG
        glEnable(GL_DEBUG_OUTPUT);
        glDebugMessageCallback(GLDebugMessageCallback, 0);
#endif
    }

    void Window::OnRender()
    {
        RenderScene();
        RenderUIElements();

        glfwSwapBuffers(m_Window.get());
        glfwPollEvents();
    }

    bool Window::IsRunning() const
    {
        return !glfwWindowShouldClose(m_Window.get());
    }

    void Window::RenderScene()
    {
        for (auto& layer : m_Layers)
        {
            layer->OnRender();
        }
    }

    void Window::RenderUIElements()
    {
        m_UIRenderer.BeginFrame();
        for (auto& layer : m_Layers)
        {
            layer->OnImGuiRender();
        }
        m_UIRenderer.Render(m_WindowProperties);
    }

}
