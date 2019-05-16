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

    void Window::OnUpdate()
    {
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
