#include "pch.h"
#include "Renderer.h"

#include "renderer/Layer.h"

namespace Graphics {
    Renderer::Renderer()
        : m_WindowProperties("OpenGL Graphics Demo", 1920, 1080)
        , m_Window(CreateGLFWWindow(m_WindowProperties))
        , m_UIRenderer(ImGuiRenderer(m_Window.get()))
        , m_Layers(m_Window.get())
    {}

    void Renderer::OnRender()
    {
        RenderScene();
        RenderUIElements();

        glfwSwapBuffers(m_Window.get());
        glfwPollEvents();
    }

    bool Renderer::IsRunning() const
    {
        return !glfwWindowShouldClose(m_Window.get());
    }

    void Renderer::RenderScene()
    {
        for (auto& layer : m_Layers)
        {
            layer->OnRender();
        }
    }

    void Renderer::RenderUIElements()
    {
        m_UIRenderer.BeginFrame();
        for (auto& layer : m_Layers)
        {
            layer->OnImGuiRender();
        }
        m_UIRenderer.Render(m_WindowProperties);
    }

}
