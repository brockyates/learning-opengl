#pragma once
#include "layers/Layer.h"
#include "ShaderHelpers.h"

#include <glm/glm.hpp>

namespace Graphics {

    class HelloWorld : public Layer
    {
    public:
        HelloWorld();

        virtual void OnUpdate() override;
        virtual void OnImGuiRender() override;

        virtual void Attach() override;
        virtual void Detach() override;
        virtual bool IsAttached() override { return m_Attached; }

        virtual std::string GetPopupText() const override;
        virtual std::string GetDescription() const override;

    private:
        unsigned int m_ShaderID = 0;
        unsigned int m_VertexArrayID = 0;
        unsigned int m_VertexBufferID = 0;
        bool m_Attached = false;

        glm::vec4 m_ClearColor = { 0.5f, 0.5f, 0.5f, 1.0f };

        std::vector<float> m_Vertexes =
        {
            0.0f,  1.0f,
           -1.0f, -1.0f,
            1.0f, -1.0f,
        };
    };

}
