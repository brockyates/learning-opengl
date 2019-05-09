#pragma once
#include "renderer/Layer.h"
#include "renderer/Shader.h"

namespace Graphics {

    class MinimalRenderDemo : public Layer
    {
    public:
        MinimalRenderDemo();
        ~MinimalRenderDemo();

        virtual void OnRender() override;
        virtual void OnImGuiRender() override;

    private:
        unsigned int m_ShaderID;
        unsigned int m_VertexBufferID;
        bool m_Enabled = true;

        std::vector<float> m_Vertexes =
        {
            0.0f,  1.0f,
           -1.0f, -1.0f,
            1.0f, -1.0f,
        };
    };

}
