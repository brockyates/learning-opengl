#pragma once
#include "layers/Layer.h"
#include "ShaderHelpers.h"

#include <glm/glm.hpp>

namespace Graphics {

    class MinimalRenderDemo : public Layer
    {
    public:
        MinimalRenderDemo();

        virtual void OnUpdate() override;
        virtual void OnImGuiRender() override;

        virtual void Attach() override;
        virtual void Detach() override;

        virtual bool IsAttached() override { return m_Attached; }

    private:
        unsigned int m_ShaderID = 0;
        unsigned int m_VertexArrayID = 0;
        unsigned int m_VertexBufferID = 0;
        bool m_Attached = false;

        glm::vec4 m_ClearColor = { 0.2f, 0.3f, 0.7f, 1.0f };

        std::vector<float> m_Vertexes =
        {
            0.0f,  1.0f,
           -1.0f, -1.0f,
            1.0f, -1.0f,
        };
    };

}
