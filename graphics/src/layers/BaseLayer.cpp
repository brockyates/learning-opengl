#include "pch.h"
#include "BaseLayer.h"
#include "renderer/Shader.h"

#include <glad/glad.h>
#include <imgui.h>

namespace Graphics {

    BaseLayer::BaseLayer()
        :m_ClearColor({ 0.2f, 0.3f, 0.7f, 1.0f })
    {}

    void BaseLayer::OnRender()
    {
        GLCall(glClear(GL_COLOR_BUFFER_BIT));
        GLCall(glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]));
    }

    void BaseLayer::OnImGuiRender()
    {
        ImGui::Begin("Demo");
            if (ImGui::CollapsingHeader("Clear Color"))
            {
                ImGui::ColorEdit4("glClearColor", &m_ClearColor[0]);
            }
        ImGui::End();
    }

}
