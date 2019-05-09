#pragma once
#include "layers/Layer.h"

#include <glm/glm.hpp>

namespace Graphics {

    class BaseLayer : public Layer
    {
    public:
        BaseLayer();

        virtual void OnUpdate() override;
        virtual void OnImGuiRender() override;

    private:
        glm::vec4 m_ClearColor;
    };

}
