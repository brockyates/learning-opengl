#include "pch.h"
#include "ApplicationBase.h"

#include "config/WindowConfig.h"
#include "events/ChangeResolutionEvent.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "Window.h"
#include "WindowMode.h"

#include <imgui.h>
#include <imgui_internal.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Graphics {

    ApplicationBase::ApplicationBase(Window* window, EventHandler<Event> eventCallback)
        : Layer(window, eventCallback, "ApplicationBase")
    {}

    void ApplicationBase::HandleInput()
    {
        ImGuiIO& io = ImGui::GetIO();

        if (m_F11Ready && (m_Window->Input.IsKeyPressed(GLFW_KEY_F11) || ImGui::IsKeyPressed(GLFW_KEY_F11)))
        {
            m_F11Ready = false;

            // TODO: Push all of these GLFW calls to Window class
            if (m_Window->IsFullscreen())
            {
                m_Window->SetMode(WindowMode::Windowed); // TODO: Fire event
                glfwHideWindow(m_Window->GetNativeWindow());
                glfwSetWindowMonitor(m_Window->GetNativeWindow(), 0, 0, 0, m_Window->GetWindowedSettings().Width, m_Window->GetWindowedSettings().Height, GLFW_DONT_CARE);
                glfwSetWindowPos(m_Window->GetNativeWindow(), m_Window->GetWindowedSettings().Xpos, m_Window->GetWindowedSettings().Ypos);
                glfwShowWindow(m_Window->GetNativeWindow());

                m_WindowStateChange = true;
            }
            else
            {
                m_Window->SetMode(WindowMode::Fullscreen);

                int width, height, xpos, ypos;

                glfwGetWindowSize(m_Window->GetNativeWindow(), &width, &height);
                glfwGetWindowPos(m_Window->GetNativeWindow(), &xpos, &ypos);

                m_Window->SetWindowedSettings({ width, height, xpos, ypos });  // TODO: Fire event

                glfwSetWindowMonitor(m_Window->GetNativeWindow(), glfwGetPrimaryMonitor(), 0, 0, m_Window->Width(), m_Window->Height(), GLFW_DONT_CARE);
                glfwShowWindow(m_Window->GetNativeWindow());
                glfwFocusWindow(m_Window->GetNativeWindow());

                m_WindowStateChange = true;
            }
        }

        if (m_Window->Input.IsKeyReleased(GLFW_KEY_F11))
        {
            m_F11Ready = true;
        }
    }

    void ApplicationBase::RenderScene()
    {
        m_WindowStateChange = false;
        HandleInput();
    }

    void ApplicationBase::RenderUI()
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ShowMainWindow();
        ShowLogWindow();
    }

    void ApplicationBase::OnImGuiRenderOverlay()
    {
        ImGui::Begin("Scene");

        //TODO: Push all of these GLFW calls to Window class
        if (ImGui::Button("Toggle Fullscreen (F11)"))
        {
            m_Window->SetMode(WindowMode::Fullscreen);

            int width, height, xpos, ypos;

            glfwGetWindowSize(m_Window->GetNativeWindow(), &width, &height);
            glfwGetWindowPos(m_Window->GetNativeWindow(), &xpos, &ypos);

            m_Window->SetWindowedSettings({ width, height, xpos, ypos }); // TODO: Fire event

            glfwSetWindowMonitor(m_Window->GetNativeWindow(), glfwGetPrimaryMonitor(), 0, 0, m_Window->Width(), m_Window->Height(), GLFW_DONT_CARE);
            glfwShowWindow(m_Window->GetNativeWindow());
            glfwFocusWindow(m_Window->GetNativeWindow());
        }

        ImGui::End();
    }

    void ApplicationBase::ShowMenuBar()
    {
        bool showFullscreenControlsPopup = false;

        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("Exit", "Alt+F4"))
                {
                    glfwSetWindowShouldClose(m_Window->GetNativeWindow(), GLFW_TRUE);
                }
                ImGui::EndMenu();
            }
            ImGui::Spacing();
            ImGui::Spacing();
            ImGui::Spacing();
            if (ImGui::BeginMenu("Video"))
            {
                if (ImGui::BeginCombo("Scene Resolution", m_Window->Resolution().DisplayName.c_str()))
                {
                    for (const auto& res : WindowConfig::SupportedResolutions)
                    {
                        bool isSelected = (m_Window->Resolution() == res);

                        if (ImGui::Selectable(res.DisplayName.c_str(), isSelected))
                        {
                            m_WindowStateChange = true;
                            m_Window->SetResolution(res); //TODO: Fire event
                            FireEvent(ChangeResolutionEvent());
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
            ImGui::Spacing();
            ImGui::Spacing();
            ImGui::Spacing();
            if (ImGui::BeginMenu("Help"))
            {
                if (ImGui::MenuItem("Fullscreen Controls"))
                {
                    showFullscreenControlsPopup = true;
                }
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }

        if (showFullscreenControlsPopup)
        {
            ImGui::OpenPopup("FullscreenControlsPopup");
        }

        if (ImGui::BeginPopup("FullscreenControlsPopup"))
        {
            ImGui::Text("Fullscreen Controls");
            ImGui::Separator();
            ImGui::Text("F11: Exit Fullscreen");
            ImGui::EndPopup();
        }
    }

    void ApplicationBase::LayoutPreset(ImGuiID dockspaceID, ImVec2 dockSize)
    {
        ImGui::DockBuilderRemoveNode(dockspaceID);
        ImGuiDockNodeFlags dockSpaceFlags = ImGuiDockNodeFlags_DockSpace;
        ImGui::DockBuilderAddNode(dockspaceID, dockSpaceFlags);
        ImGui::DockBuilderSetNodeSize(dockspaceID, dockSize);

        ImGuiID dockMain = dockspaceID;
        ImGuiID dockBottom = ImGui::DockBuilderSplitNode(dockMain, ImGuiDir_Down, 0.22f, NULL, &dockMain);
        ImGuiID dockLeft = ImGui::DockBuilderSplitNode(dockMain, ImGuiDir_Left, 0.30f, NULL, &dockMain);

        ImGui::DockBuilderDockWindow("Scene", dockMain);
        ImGui::DockBuilderDockWindow("DemoWidget", dockLeft);
        ImGui::DockBuilderDockWindow("Log", dockBottom);
        ImGui::DockBuilderFinish(dockspaceID);
    }

    void ApplicationBase::ShowMainWindow()
    {
        static bool opt_fullscreen_persistant = true;
        bool opt_fullscreen = opt_fullscreen_persistant;
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

        ImVec2 dockSize;

        // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
        // because it would be confusing to have two docking targets within each others.
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        if (opt_fullscreen)
        {
            ImGuiViewport* viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->Pos);
            ImGui::SetNextWindowSize(viewport->Size);
            dockSize = viewport->Size;
            ImGui::SetNextWindowViewport(viewport->ID);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
            window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        }

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("MainDockspaceWindow", 0, window_flags);
        ImGui::PopStyleVar();

        if (opt_fullscreen)
            ImGui::PopStyleVar(2);

        // DockSpace
        ImGuiIO& io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            ImGuiID dockspace_id = ImGui::GetID("MainDockspace");

            if (ImGui::DockBuilderGetNode(dockspace_id) == NULL)
                LayoutPreset(dockspace_id, dockSize);

            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        }

        ShowMenuBar();
        ImGui::End();
    }

    void ApplicationBase::ShowLogWindow()
    {
        ImGui::Begin("Log", 0, ImGuiWindowFlags_HorizontalScrollbar);
            
            const auto& logString = Graphics::Utils::Log::GetLogStream().rdbuf()->str();
            ImGui::TextUnformatted(logString.c_str());
            ImGui::SetScrollHereY(1.0f);

        ImGui::End();
    }

}
