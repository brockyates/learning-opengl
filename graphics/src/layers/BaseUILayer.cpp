#include "pch.h"
#include "BaseUILayer.h"

#include <imgui.h>
#include <examples/imgui_impl_glfw.h>
#include <examples/imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>

namespace Graphics {

    void BaseUILayer::OnImGuiRender()
    {
        ImGui::Begin("OpenGL Graphics Demo", &m_Active, ImGuiWindowFlags_MenuBar);

        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("Exit", "Alt+F4")) { m_Active = false; }
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }

        ImGui::End();
    }

}
