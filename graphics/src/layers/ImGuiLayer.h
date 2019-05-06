#pragma once
#include "renderer/Layer.h"

#include <GLFW/glfw3.h>

namespace Graphics {

    class ImGuiLayer : public Layer
    {
    public:
        virtual void OnImGuiRender() override;

    private:
        float m_Time = 0.0f;
    };

}
