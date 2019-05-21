#pragma once

#include "BaseLayer.h"
#include "events/Event.h"
#include "imgui/ImGuiRenderer.h"
#include "Layer.h"
#include "Window.h"

namespace Graphics {

    class Layer;
    struct WindowProperties;

    class LayerManager
    {
    public:
        LayerManager(const Window& window, EventHandler<Event> eventCallback);
        ~LayerManager() = default;

        LayerManager(LayerManager&&) = default;
        LayerManager& operator=(LayerManager&&) = default;

        void RenderScene();
        void RenderUI();
        void OnEvent(const Event& event);

    private:
        std::vector<std::unique_ptr<Layer>> LayerManager::MakeLayers(const Window& window, EventHandler<Event> eventCallback);
        void ShowDemoSelector();
        void UpdateActiveLayer(Layer* activeLayer);

    private:
        std::vector<std::unique_ptr<Layer>> m_Layers;
        BaseLayer m_BaseLayer;
        Layer* m_ActiveLayer;
        ImGuiRenderer m_UIRenderer;
    };

}
