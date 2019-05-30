#pragma once

#include "events/Event.h"

#include "BaseLayer.h"
#include "RenderTargetLayer.h"

#include "imgui/ImGuiRenderer.h"

namespace graphics {

    class Window;

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
        RenderTargetLayer m_RenderTarget;

        Layer* m_ActiveLayer;
        ImGuiRenderer m_UIRenderer;
    };

}
