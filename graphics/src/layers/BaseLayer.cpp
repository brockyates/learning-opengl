#include "pch.h"
#include "BaseLayer.h"

#include "config/WindowDefaults.h"
#include "Window.h"

#include <imgui.h>
#include <imgui_internal.h> //Needed to create docking layout presets

namespace Graphics {

    BaseLayer::BaseLayer(const Window& window, EventHandler<Event> eventCallback)
        : Layer(window, eventCallback, "BaseLayer")
    {}

    void BaseLayer::HandleInput()
    {
        if (m_Window.IsFullscreen())
        {
            HandleFullscreenInput();
        }
        else
        {
            HandleWindowedInput();
        }

        if (m_Window.Input().IsKeyReleased(GLFW_KEY_F11))
        {
            m_F11Ready = true;
        }

        if (m_Window.Input().IsKeyReleased(GLFW_KEY_ESCAPE))
        {
            m_EscReady = true;
        }
    }

    void BaseLayer::HandleFullscreenInput()
    {
        if (m_F11Ready && (m_Window.Input().IsKeyPressed(GLFW_KEY_F11)))
        {
            m_F11Ready = false;
            FireEvent(ChangeToWindowedEvent());
        }

        if (m_EscReady && (m_Window.Input().IsKeyPressed(GLFW_KEY_ESCAPE)))
        {
            m_EscReady = false;
            FireEvent(ChangeToWindowedEvent());
        }
    }

    void BaseLayer::HandleWindowedInput()
    {
        if (m_F11Ready && (m_Window.Input().IsKeyPressed(GLFW_KEY_F11)))
        {
            m_F11Ready = false;
            FireEvent(ChangeToFullscreenEvent());
        }
    }

    void BaseLayer::RenderScene()
    {
        HandleInput();
    }

    void BaseLayer::RenderUI()
    {
        ShowMainWindow();
        ShowLogWindow();
    }

    void BaseLayer::OnImGuiRenderOverlay()
    {
        ImGui::Begin("Scene");

        if (ImGui::Button("Toggle Fullscreen (F11)"))
        {
            FireEvent(ChangeToFullscreenEvent());
        }

        ImGui::End();
    }

    void BaseLayer::ShowMenuBar()
    {
        bool showFullscreenControlsPopup = false;

        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("Exit", "Alt+F4"))
                {
                    FireEvent(WindowCloseEvent());
                }
                ImGui::EndMenu();
            }
            ImGui::Spacing();
            ImGui::Spacing();
            ImGui::Spacing();
            if (ImGui::BeginMenu("Video"))
            {
                if (ImGui::BeginCombo("Scene Resolution", m_Window.Resolution().DisplayName.c_str()))
                {
                    for (const auto& resolution : WindowDefaults::SupportedResolutions)
                    {
                        bool isSelected = (m_Window.Resolution() == resolution);

                        if (ImGui::Selectable(resolution.DisplayName.c_str(), isSelected))
                        {
                            FireEvent(ChangeResolutionEvent(resolution));
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

    void BaseLayer::LayoutPreset(ImGuiID dockspaceID, ImVec2 dockSize)
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

    void BaseLayer::ShowMainWindow()
    {
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;
        ImVec2 dockSize;

        // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
        // because it would be confusing to have two docking targets within each others.
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        auto viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->Pos);
        ImGui::SetNextWindowSize(viewport->Size);
        dockSize = viewport->Size;
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("MainDockspaceWindow", 0, window_flags);
        ImGui::PopStyleVar(3);

        ImGuiIO& io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            ImGuiID dockspace_id = ImGui::GetID("MainDockspace");

            if (ImGui::DockBuilderGetNode(dockspace_id) == NULL) // Create default DockSpace on first run
                LayoutPreset(dockspace_id, dockSize);

            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        }

        ShowMenuBar();
        ImGui::End();
    }

    void BaseLayer::ShowLogWindow()
    {
        ImGui::Begin("Log", 0, ImGuiWindowFlags_HorizontalScrollbar);
            
            const auto& logString = Graphics::Utils::Log::GetLogStream().rdbuf()->str();
            ImGui::TextUnformatted(logString.c_str());
            ImGui::SetScrollHereY(1.0f);

        ImGui::End();
    }

}
