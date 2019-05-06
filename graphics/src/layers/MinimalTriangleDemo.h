#pragma once
#include "renderer/Layer.h"
#include "renderer/Shader.h"

namespace Graphics {

    class MinimalTriangleDemo : public Layer
    {
    public:
        MinimalTriangleDemo();

        virtual void OnRender() override;

    private:
        Shader m_Shader;
        unsigned int m_VertexBufferID;

        float m_Vertexes[6] =
        {
            0.0f,  1.0f,
           -1.0f, -1.0f,
            1.0f, -1.0f,
        };
    };

}
