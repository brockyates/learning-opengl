#pragma once
#include "Layer.h"

namespace Graphics {

    class BaseLayer : public Layer
    {
    public:
        virtual void OnUpdate() override;
    };

}
