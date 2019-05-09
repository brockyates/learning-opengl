#include "pch.h"
#include "LayerManager.h"

#include "layers/Layer.h"

//Layers
#include "layers/BaseLayer.h"
#include "layers/BaseUILayer.h"
#include "layers/MinimalRenderDemo.h"

namespace Graphics {

    LayerManager::LayerManager(GLFWwindow* window)
    {
        m_Layers.emplace_back(std::make_unique<BaseLayer>());
        m_Layers.emplace_back(std::make_unique<BaseUILayer>(window));
        m_Layers.emplace_back(std::make_unique<MinimalRenderDemo>());
    }

}
