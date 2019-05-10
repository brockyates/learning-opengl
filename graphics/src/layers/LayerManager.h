#pragma once

#include "BaseUILayer.h"
#include "Layer.h"

namespace Graphics {

    class Layer;

    class LayerManager
    {
    public:
        LayerManager(GLFWwindow* window);

        void OnUpdate();
        void OnImGuiRender();

    private:
        void ShowDemoSelector();
        void UpdateActiveLayer(Layer* activeLayer);

    private:
        BaseUILayer m_BaseUILayer;

        std::vector<std::unique_ptr<Layer>> m_Layers;
        Layer* m_ActiveLayer;
    };

}
