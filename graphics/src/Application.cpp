#include "pch.h"
#include "Application.h"

#include "logging/Log.h"

#include "window/Window.h"

namespace Graphics {

    Application::Application()
        : window_(std::make_unique<Window>([this](const Event& e) { return OnEvent(e); }))
        , layerManager_(*window_, [this](const Event& e) { return OnEvent(e); })
    {}

    void Application::Start()
    {
        LOG_INFO("Main application loop started");

        while (!window_->ShouldClose())
        {
            layerManager_.RenderScene();

            if (!window_->IsFullscreen())
            {
                layerManager_.RenderUi();
            }

            window_->Update();
        }

        LOG_INFO("Main application loop stopped");
    }

    // Top-level event handler
    void Application::OnEvent(const Event& event)
    {
        window_->OnEvent(event);
        layerManager_.OnEvent(event);
    }

}
