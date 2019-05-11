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
            if (m_IsUIEnabled)
                return;

            m_IsUIEnabled = true;
            glfwSetWindowMonitor(m_Window, 0, 0, 0, 1024, 768, GLFW_DONT_CARE);
            glfwHideWindow(m_Window);
        }

        if (m_Input.IsKeyPressed(GLFW_KEY_0) || ImGui::IsKeyPressed(GLFW_KEY_0))
        {
            m_IsUIEnabled = false;
        }

        if (m_Input.IsKeyPressed(GLFW_KEY_9) || ImGui::IsKeyPressed(GLFW_KEY_9))
        {
            m_IsUIEnabled = true;
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
            m_IsUIEnabled = false;
            glfwSetWindowMonitor(m_Window, glfwGetPrimaryMonitor(), 0, 0, 1920, 1080, GLFW_DONT_CARE);
            glfwShowWindow(m_Window);
        }
        ImGui::End();
    }

}
