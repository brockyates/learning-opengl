#include "pch.h"
#include "Application.h"

#include "imgui/ImGuiRenderer.h"
#include "layers/LayerManager.h"
#include "Window.h"

namespace Graphics {

    void Application::Start()
    {
        Window window;

        LayerManager layerManager(window.Context());
        ImGuiRenderer uiRenderer(window.Context());

        LOG_INFO("Main application loop started");

        while (!window.ShouldClose() && !layerManager.WindowShouldClose())
        {
            layerManager.OnUpdate();

            if (!window.IsFullscreen())
            {
                uiRenderer.BeginFrame();
                layerManager.OnImGuiRender();
                uiRenderer.Render(window.Context()->Properties);
            }

            window.OnUpdate();
        }

        LOG_INFO("Main application loop stopped");
    }

}
