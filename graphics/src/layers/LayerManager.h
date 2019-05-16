#pragma once

#include "ApplicationBase.h"
#include "Layer.h"
#include "WindowContext.h"

namespace Graphics {

    class Layer;
    struct WindowProperties;

    class LayerManager
    {
    public:
        LayerManager(WindowContext* window);

        void OnUpdate();
        void OnImGuiRender();

        bool WindowShouldClose() const { return m_ApplicationBase.WindowShouldClose(); }

    private:
        void ShowDemoSelector();
        void UpdateActiveLayer(Layer* activeLayer);

    private:
        const WindowContext* m_Window;
        ApplicationBase m_ApplicationBase;

        std::vector<std::unique_ptr<Layer>> m_Layers;
        Layer* m_ActiveLayer;
    };

}
