#pragma once

#include "ApplicationBase.h"
#include "imgui/ImGuiRenderer.h"
#include "Layer.h"
#include "WindowContext.h"

namespace Graphics {

    class Layer;
    struct WindowProperties;

    class LayerManager
    {
    public:
        LayerManager(WindowContext* window);
        ~LayerManager() = default;

        LayerManager(LayerManager&&) = default;
        LayerManager& operator=(LayerManager&&) = default;

        void RenderScene();
        void RenderUI();

    private:
        void ShowDemoSelector();
        void UpdateActiveLayer(Layer* activeLayer);

    private:
        const WindowContext* m_Window;
        ApplicationBase m_ApplicationBase;

        std::vector<std::unique_ptr<Layer>> m_LayerManager;
        Layer* m_ActiveLayer;

        ImGuiRenderer m_UIRenderer;
    };

}
