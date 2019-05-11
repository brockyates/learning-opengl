#include "pch.h"
#include "BaseUILayer.h"

#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include <imgui.h>
#include <GLFW/glfw3.h>

namespace Graphics {

    BaseUILayer::BaseUILayer(GLFWwindow* window)
        : Layer("BaseUILayer")
        , m_Window(window)
        , m_Input(window)
    {}

    void BaseUILayer::HandleInput()
    {
        ImGuiIO& io = ImGui::GetIO();

        if (ImGui::IsMousePosValid())
        {
            /* Too noisy in the logs, but useful for documentation for now
            LOG_TRACE([&]()
            {
                std::stringstream ss;
                ss << "Mouse pos: " << io.MousePos.x << "," << io.MousePos.y;
                return ss.str();
            }());
            */
        }

        if (m_Input.IsKeyPressed(GLFW_KEY_ESCAPE) || ImGui::IsKeyPressed(GLFW_KEY_ESCAPE))
        {
            LOG_TRACE("Escape key is pressed");
        }

        if (m_Input.IsMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT) || io.MouseDownDuration[GLFW_MOUSE_BUTTON_LEFT] >= 0.0f)
        {
            LOG_TRACE("Left mouse button is pressed");
        }

        if (m_Input.IsMouseButtonPressed(GLFW_MOUSE_BUTTON_RIGHT) || io.MouseDownDuration[GLFW_MOUSE_BUTTON_RIGHT] >= 0.0f)
        {
            LOG_TRACE("Right mouse button is pressed");
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

        if (!isMainUIOpen)
        {
            m_IsWindowOpen = false;
        }

        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("Exit", "Alt+F4"))
                {
                    m_IsWindowOpen = false;
                }
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Window"))
            {
                if (ImGui::MenuItem("Show GLFW Window"))
                {
                    glfwShowWindow(m_Window);
                }
                if (ImGui::MenuItem("Hide GLFW Window"))
                {
                    glfwHideWindow(m_Window);
                }
                ImGui::EndMenu();
            }

            ImGui::EndMenuBar();
        }

        ImGui::End();
    }

    void BaseUILayer::ShowLogWindow()
    {
        ImGui::SetNextWindowSize(ImVec2(500, 400), ImGuiCond_FirstUseEver);
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
        ImGui::End();
    }

}
