#pragma once
#include "layers/Layer.h"

#include "config/WindowConfig.h"
#include "Window.h"
#include "WindowedSettings.h"

#include <imgui.h>

namespace Graphics {

    class ApplicationBase : public Layer
    {
    public:
        ApplicationBase(Window* window);

        virtual void RenderScene() override;
        virtual void RenderUI() override;
        virtual bool IsAttached() override { return true; }

        void OnImGuiRenderOverlay();

        bool HasSceneResolutionChanged() const { return m_WindowStateChange; }

    private:
        WindowedSettings InitializeWindowedSettings();
        void HandleInput();

        void LayoutPreset(ImGuiID dockspaceID, ImVec2 dockSize);
        void ShowMenuBar();
        void ShowMainWindow();
        void ShowLogWindow();

    private:
        bool m_F11Ready = true;
        bool m_WindowStateChange = false;

        WindowedSettings m_WindowedSettings; // TODO: belongs in Window class
    };

}
