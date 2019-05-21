#include "pch.h"
#include "Application.h"

#include "Window.h"

namespace Graphics {

    Application::Application()
        : m_Window(std::make_unique<Window>())
        , m_LayerManager(*m_Window, [this](const Event& e) { return OnEvent(e); })
    {}

    void Application::Start()
    {
        LOG_INFO("Main application loop started");

        while (!m_Window->ShouldClose())
        {
            m_LayerManager.RenderScene();

            if (!m_Window->IsFullscreen())
            {
                m_LayerManager.RenderUI();
            }

            m_Window->Update();
        }

        LOG_INFO("Main application loop stopped");
    }

    // Top-level event handler
    void Application::OnEvent(const Event& event)
    {
        m_Window->OnEvent(event);
        m_LayerManager.OnEvent(event);
    }

}
