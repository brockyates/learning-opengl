#include "pch.h"
#include "BaseUILayer.h"

#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include <imgui.h>
#include <GLFW/glfw3.h>

namespace Graphics {

    BaseUILayer::BaseUILayer(GLFWwindow * window)
        : m_Window(window)
    {}

    void BaseUILayer::OnImGuiRender()
    {
        if (!m_IsWindowOpen)
        {
            CloseApplication();
        }

        ImGui::Begin("OpenGL Graphics Demo", &m_IsWindowOpen, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoCollapse);

        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("Exit", "Alt+F4"))
                {
                    CloseApplication();
                }
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }

        ImGui::End();
    }

    void BaseUILayer::CloseApplication() const
    {
        glfwSetWindowShouldClose(m_Window, GLFW_TRUE);
    }

}
