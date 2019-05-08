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

        ShowMainWindow();
        ShowLogWindow();
        ShowGLWindow();
        ShowDemoWidget();
    }

    void BaseUILayer::CloseApplication() const
    {
        glfwSetWindowShouldClose(m_Window, GLFW_TRUE);
    }

    void BaseUILayer::ShowMainWindow()
    {
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

    void BaseUILayer::ShowLogWindow()
    {
        bool isLogWindowOpen = true;

        ImGui::SetNextWindowSize(ImVec2(500, 400), ImGuiCond_FirstUseEver);
        ImGui::Begin("Output", &isLogWindowOpen, ImGuiWindowFlags_HorizontalScrollbar);
            
            const auto& logString = Graphics::Utils::Log::GetLogStream().rdbuf()->str();
            ImGui::TextUnformatted(logString.c_str());

        ImGui::End();
    }

    void BaseUILayer::ShowGLWindow()
    {
        ImGui::Begin("Scene");
        ImGui::End();
    }

    void BaseUILayer::ShowDemoWidget()
    {
        ImGui::Begin("Demo");
        ImGui::End();
    }

}
