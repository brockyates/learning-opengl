#include "pch.h"
#include "Application.h"

#include "imgui/ImGuiRenderer.h"
#include "layers/SceneManager.h"
#include "Window.h"

namespace Graphics {

    void Application::Start()
    {
        auto window = std::make_unique<Window>();
        auto sceneManager = SceneManager(window->Context());

        LOG_INFO("Main application loop started");

        while (!window->ShouldClose())
        {
            sceneManager.RenderScene();

            if (!window->IsFullscreen())
            {
                sceneManager.RenderUI();
            }

            window->Update();
        }

        LOG_INFO("Main application loop stopped");
    }

}
