#include "pch.h"
#include "LayerManager.h"

#include "renderer/Layer.h"

//Layers
#include "layers/BaseLayer.h"
#include "layers/BaseUILayer.h"
#include "layers/MinimalTriangleDemo.h"

namespace Graphics {

    LayerManager::LayerManager()
    {
        m_Layers.emplace_back(std::make_unique<BaseLayer>());
        m_Layers.emplace_back(std::make_unique<BaseUILayer>());
        m_Layers.emplace_back(std::make_unique<MinimalTriangleDemo>());
    }

}
