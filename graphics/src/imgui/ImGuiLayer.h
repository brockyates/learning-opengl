#pragma once
#include "Layer.h"

#include <GLFW/glfw3.h>

namespace Graphics {

    class ImGuiLayer : public Layer
    {
    public:
        virtual void OnAttach(GLFWwindow* window) override;
        virtual void OnDetach() override;
        virtual void OnImGuiRender() override;

        void Begin();
        void End(unsigned int width, unsigned int height);

    private:
        float m_Time = 0.0f;
    };

}
