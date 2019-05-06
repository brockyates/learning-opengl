#pragma once

#include "renderer/Layer.h"

namespace Graphics {

    class Layer;

    class LayerManager
    {
    public:
        LayerManager();

        std::vector<std::unique_ptr<Layer>>::iterator begin() { return m_Layers.begin(); }
        std::vector<std::unique_ptr<Layer>>::iterator end() { return m_Layers.end(); }

    private:
        std::vector<std::unique_ptr<Layer>> m_Layers;
    };

}
