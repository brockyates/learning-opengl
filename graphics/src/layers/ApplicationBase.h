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

        virtual void RenderScene(Window* window) override;
        virtual void RenderUI(Window* window) override;
        virtual bool IsAttached() override { return true; }

        void OnImGuiRenderOverlay(Window* window);

        bool HasSceneResolutionChanged() const { return m_WindowStateChange; }

    private:
        WindowedSettings InitializeWindowedSettings(Window* window);
        void HandleInput(Window* window);

        void LayoutPreset(ImGuiID dockspaceID, ImVec2 dockSize);
        void ShowMenuBar(Window* window);
        void ShowMainWindow(Window* window);
        void ShowLogWindow();

    private:
        bool m_F11Ready = true;
        bool m_WindowStateChange = false;

        WindowedSettings m_WindowedSettings; // TODO: belongs in Window class
    };

}
