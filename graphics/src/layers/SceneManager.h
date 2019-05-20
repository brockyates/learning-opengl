#pragma once

#include "ApplicationBase.h"
#include "events/Event.h"
#include "imgui/ImGuiRenderer.h"
#include "Layer.h"
#include "Window.h"

namespace Graphics {

    class Layer;
    struct WindowProperties;

    class SceneManager
    {
    public:
        SceneManager(Window* window, EventHandler<Event> eventCallback);
        ~SceneManager() = default;

        SceneManager(SceneManager&&) = default;
        SceneManager& operator=(SceneManager&&) = default;

        void RenderScene();
        void RenderUI();

        void OnEvent(Event& event);

    private:
        std::vector<std::unique_ptr<Layer>> SceneManager::MakeLayers(Window* window, EventHandler<Event> eventCallback);
        void ShowDemoSelector();
        void UpdateActiveLayer(Layer* activeLayer);

    private:
        ApplicationBase m_ApplicationBase;
        std::vector<std::unique_ptr<Layer>> m_Layers;
        Layer* m_ActiveLayer;
        ImGuiRenderer m_UIRenderer;
    };

}
