#pragma once
#include "renderer/Layer.h"

namespace Graphics {

    class BaseLayer : public Layer
    {
    public:
        virtual void OnRender() override;
    };

}
