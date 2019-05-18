#include "pch.h"
#include "Application.h"

#include "imgui/ImGuiRenderer.h"
#include "layers/LayerManager.h"
#include "Window.h"

namespace Graphics {

    void Application::Start()
    {
        auto window = std::make_unique<Window>();
        auto layerManager = LayerManager(window->Context());

        LOG_INFO("Main application loop started");

        while (!window->ShouldClose())
        {
            layerManager.RenderScene();

            if (!window->IsFullscreen())
            {
                layerManager.RenderUI();
            }

            window->OnUpdate();
        }

        LOG_INFO("Main application loop stopped");
    }

}
