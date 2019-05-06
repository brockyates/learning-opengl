#include "pch.h"
#include "LayerManager.h"

#include "renderer/Layer.h"

//Layers
#include "layers/BaseLayer.h"
#include "layers/ImGuiLayer.h"
#include "layers/MinimalTriangleDemo.h"

namespace Graphics {

    LayerManager::LayerManager()
    {
        m_Layers.emplace_back(std::make_unique<BaseLayer>());
        m_Layers.emplace_back(std::make_unique<ImGuiLayer>());
        m_Layers.emplace_back(std::make_unique<MinimalTriangleDemo>());
    }

}
