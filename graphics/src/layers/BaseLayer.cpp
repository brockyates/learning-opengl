#include "pch.h"
#include "BaseLayer.h"

#include "window/WindowDefaults.h"

#include "logging/Log.h"

#include "window/Window.h"

#include <imgui_internal.h> //Needed to create docking layout presets
#include <utility>

namespace Graphics
{
    BaseLayer::BaseLayer(const Window& window, EventHandler<Event> eventCallback)
        : Layer(window, std::move(eventCallback), "BaseLayer")
    {}

    void BaseLayer::HandleInput()
    {
        if (window_.IsFullscreen())
        {
            HandleFullscreenInput();
        }
        else
        {
            HandleWindowedInput();
        }

        if (window_.Input().IsKeyReleased(GLFW_KEY_F11))
        {
            f11Ready_ = true;
        }

        if (window_.Input().IsKeyReleased(GLFW_KEY_ESCAPE))
        {
            escReady_ = true;
        }
    }

    void BaseLayer::HandleFullscreenInput()
    {
        if (f11Ready_ && window_.Input().IsKeyPressed(GLFW_KEY_F11))
        {
            f11Ready_ = false;
            FireEvent(ChangeToWindowedEvent());
        }

        if (escReady_ && window_.Input().IsKeyPressed(GLFW_KEY_ESCAPE))
        {
            escReady_ = false;
            FireEvent(ChangeToWindowedEvent());
        }
    }

    void BaseLayer::HandleWindowedInput()
    {
        if (f11Ready_ && window_.Input().IsKeyPressed(GLFW_KEY_F11))
        {
            f11Ready_ = false;
            FireEvent(ChangeToFullscreenEvent());
        }
    }

    void BaseLayer::RenderScene()
    {
        HandleInput();
    }

    void BaseLayer::RenderUi()
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
        auto showFullscreenControlsPopup = false;

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
                if (ImGui::BeginCombo("Scene Resolution", window_.Resolution().DisplayName.c_str()))
                {
                    for (const auto& resolution : WindowDefaults::SupportedResolutions)
                    {
                        const auto isSelected = window_.Resolution() == resolution;

                        if (ImGui::Selectable(resolution.DisplayName.c_str(), isSelected))
                        {
                            FireEvent(ResolutionChangeEvent(resolution));
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

    void BaseLayer::LayoutPreset(const ImGuiID dockspaceId, const ImVec2 dockSize)
    {
        ImGui::DockBuilderRemoveNode(dockspaceId);
        const ImGuiDockNodeFlags dockSpaceFlags = ImGuiDockNodeFlags_DockSpace;
        ImGui::DockBuilderAddNode(dockspaceId, dockSpaceFlags);
        ImGui::DockBuilderSetNodeSize(dockspaceId, dockSize);

        auto dockMain = dockspaceId;
        const auto dockBottom = ImGui::DockBuilderSplitNode(dockMain, ImGuiDir_Down, 0.22f, nullptr, &dockMain);
        const auto dockLeft = ImGui::DockBuilderSplitNode(dockMain, ImGuiDir_Left, 0.30f, nullptr, &dockMain);

        ImGui::DockBuilderDockWindow("Scene", dockMain);
        ImGui::DockBuilderDockWindow("DemoWidget", dockLeft);
        ImGui::DockBuilderDockWindow("Log", dockBottom);
        ImGui::DockBuilderFinish(dockspaceId);
    }

    void BaseLayer::ShowMainWindow()
    {
        static ImGuiDockNodeFlags dockspaceFlags = ImGuiDockNodeFlags_None;

        // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dock-able into,
        // because it would be confusing to have two docking targets within each others.
        auto windowFlags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        const auto viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->Pos);
        ImGui::SetNextWindowSize(viewport->Size);
        const auto dockSize = viewport->Size;
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        windowFlags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        windowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

        ImGui::Begin("MainDockspaceWindow", nullptr, windowFlags);
        ImGui::PopStyleVar(3);

        auto& io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            const auto dockspaceId = ImGui::GetID("MainDockspace");

            if (ImGui::DockBuilderGetNode(dockspaceId) == nullptr) // Create default DockSpace on first run
                LayoutPreset(dockspaceId, dockSize);

            ImGui::DockSpace(dockspaceId, ImVec2(0.0f, 0.0f), dockspaceFlags);
        }

        ShowMenuBar();
        ImGui::End();
    }

    void BaseLayer::ShowLogWindow() const
    {
        ImGui::Begin("Log", nullptr, ImGuiWindowFlags_HorizontalScrollbar);
            
            const auto& logString = Utils::Log::GetLogStream().rdbuf()->str();
            ImGui::TextUnformatted(logString.c_str());
            ImGui::SetScrollHereY(1.0f);

        ImGui::End();
    }
}
