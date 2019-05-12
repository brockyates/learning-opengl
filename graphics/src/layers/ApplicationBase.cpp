#include "pch.h"
#include "ApplicationBase.h"

#include "WindowContext.h"

#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include <imgui.h>
#include <GLFW/glfw3.h>

namespace Graphics {

    ApplicationBase::ApplicationBase(const WindowContext* window)
        : Layer(window, "ApplicationBase")
    {}

    void ApplicationBase::HandleInput()
    {
        ImGuiIO& io = ImGui::GetIO();

        if (m_Window->Input.IsKeyPressed(GLFW_KEY_ESCAPE) || ImGui::IsKeyPressed(GLFW_KEY_ESCAPE))
        {
            if (m_Window->Properties.Mode == WindowMode::Fullscreen)
            {
                m_NextWindowMode = WindowMode::Windowed;
            }
        }
    }

    void ApplicationBase::OnUpdate()
    {
        HandleInput();
    }

    void ApplicationBase::OnImGuiRender()
    {
        ShowMainWindow();
        ShowLogWindow();
        ShowGLWindow();
        ShowDemoWidget();
    }

    void ApplicationBase::ShowMainWindow()
    {
        bool isMainUIOpen = true;

        ImGui::Begin("OpenGL Graphics Demo", &isMainUIOpen, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoCollapse);

        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("Exit", "Alt+F4"))
                {
                    isMainUIOpen = false;
                }
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Video"))
            {
                if (ImGui::BeginCombo("Resolution", m_FullscreenResolution.DisplayName.c_str()))
                {
                    for (const auto& res : SupportedResolutions)
                    {
                        bool isSelected = (m_FullscreenResolution == res);

                        if (ImGui::Selectable(res.DisplayName.c_str(), isSelected))
                        {
                            m_FullscreenResolution = res;
                        }

                        if (isSelected)
                        {
                            ImGui::SetItemDefaultFocus();
                        }
                    }

                    ImGui::EndCombo();
                }

                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Help"))
            {
                if (ImGui::MenuItem("Fullscreen Controls"))
                {
                }
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }

        if (!isMainUIOpen)
        {
            m_IsWindowOpen = false;
        }

        ImGui::End();
    }

    void ApplicationBase::ShowLogWindow()
    {
        ImGui::Begin("Output", 0, ImGuiWindowFlags_HorizontalScrollbar);
            
            const auto& logString = Graphics::Utils::Log::GetLogStream().rdbuf()->str();
            ImGui::TextUnformatted(logString.c_str());
            ImGui::SetScrollHereY(1.0f);

        ImGui::End();
    }

    void ApplicationBase::ShowGLWindow()
    {
        ImGui::Begin("Scene", 0, ImGuiWindowFlags_NoCollapse);
        ImGui::End();
    }

    void ApplicationBase::ShowDemoWidget()
    {
        ImGui::Begin("Demos", 0);
        if (ImGui::Button("Go Fullscreen"))
        {
            m_NextWindowMode = WindowMode::Fullscreen;
        }
        ImGui::End();
    }

}
