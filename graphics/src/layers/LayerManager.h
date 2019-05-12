#pragma once

#include "ApplicationBase.h"
#include "Layer.h"

namespace Graphics {

    class Layer;
    struct WindowProperties;

    class LayerManager
    {
    public:
        LayerManager(const WindowContext* window);

        void OnUpdate();
        void OnImGuiRender();

        bool WindowShouldClose() const { return m_ApplicationBase.WindowShouldClose(); }
        WindowMode NextWindowMode() const { return m_ApplicationBase.NextWindowMode(); }

        void OnWindowStateChange(const WindowContext* window);

    private:
        void ShowDemoSelector();
        void UpdateActiveLayer(Layer* activeLayer);

    private:
        ApplicationBase m_ApplicationBase;

        std::vector<std::unique_ptr<Layer>> m_Layers;
        Layer* m_ActiveLayer;
    };

}
