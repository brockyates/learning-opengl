#include "pch.h"
#include "BaseUILayer.h"

#include "WindowContext.h"

#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include <imgui.h>
#include <GLFW/glfw3.h>

namespace Graphics {

    BaseUILayer::BaseUILayer(const WindowContext* window)
        : Layer(window, "BaseUILayer")
    {}

    void BaseUILayer::HandleInput()
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

    void BaseUILayer::OnUpdate()
    {
        HandleInput();
    }

    void BaseUILayer::OnImGuiRender()
    {
        ShowMainWindow();
        ShowLogWindow();
        ShowGLWindow();
        ShowDemoWidget();
    }

    void BaseUILayer::ShowMainWindow()
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
                if (ImGui::BeginMenu("Set fullscreen resolution..."))
                {
                    if (ImGui::MenuItem("640 x 480"))
                    {

                    }
                    if (ImGui::MenuItem("800 x 600"))
                    {

                    }
                    if (ImGui::MenuItem("1024 x 768"))
                    {

                    }
                    if (ImGui::MenuItem("1280 x 720 (720p)"))
                    {

                    }
                    if (ImGui::MenuItem("1280 x 800"))
                    {

                    }
                    if (ImGui::MenuItem("1366 x 768"))
                    {

                    }
                    if (ImGui::MenuItem("1440 x 900"))
                    {

                    }
                    if (ImGui::MenuItem("1600 x 900 (900p)"))
                    {

                    }
                    if (ImGui::MenuItem("1600 x 1200"))
                    {

                    }
                    if (ImGui::MenuItem("920 x 1080 (1080p)"))
                    {

                    }
                    if (ImGui::MenuItem("1920 x 1200"))
                    {

                    }
                    if (ImGui::MenuItem("2560 x 1440"))
                    {

                    }
                    if (ImGui::MenuItem("2560 x 1600"))
                    {

                    }
                    if (ImGui::MenuItem("3840 x 2160 (4k)"))
                    {

                    }
                    ImGui::EndMenu();
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

    void BaseUILayer::ShowLogWindow()
    {
        ImGui::Begin("Output", 0, ImGuiWindowFlags_HorizontalScrollbar);
            
            const auto& logString = Graphics::Utils::Log::GetLogStream().rdbuf()->str();
            ImGui::TextUnformatted(logString.c_str());
            ImGui::SetScrollHereY(1.0f);

        ImGui::End();
    }

    void BaseUILayer::ShowGLWindow()
    {
        ImGui::Begin("Scene", 0, ImGuiWindowFlags_NoCollapse);
        ImGui::End();
    }

    void BaseUILayer::ShowDemoWidget()
    {
        ImGui::Begin("Demos", 0);
        if (ImGui::Button("Go Fullscreen"))
        {
            m_NextWindowMode = WindowMode::Fullscreen;
        }
        ImGui::End();
    }

}
