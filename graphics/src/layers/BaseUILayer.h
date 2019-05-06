#pragma once
#include "renderer/Layer.h"

namespace Graphics {

    class BaseUILayer : public Layer
    {
    public:
        virtual void OnImGuiRender() override;

    private:
        bool m_Active = true;
    };

}
