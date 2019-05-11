#pragma once

#include "BaseUILayer.h"
#include "Layer.h"

namespace Graphics {

    class Layer;
    struct WindowProperties;

    class LayerManager
    {
    public:
        LayerManager(const WindowProperties& windowProperties, GLFWwindow* window);

        void OnUpdate();
        void OnImGuiRender();

        bool WindowShouldClose() const { return m_BaseUILayer.WindowShouldClose(); }

    private:
        void ShowDemoSelector();
        void UpdateActiveLayer(Layer* activeLayer);

    private:
        BaseUILayer m_BaseUILayer;

        std::vector<std::unique_ptr<Layer>> m_Layers;
        Layer* m_ActiveLayer;
    };

}
