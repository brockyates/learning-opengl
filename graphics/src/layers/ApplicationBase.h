#pragma once
#include "layers/Layer.h"

#include "config/WindowConfig.h"

#include "WindowContext.h"
#include "WindowProperties.h"
#include "WindowedSettings.h"

#include <imgui.h>

namespace Graphics {

    class ApplicationBase : public Layer
    {
    public:
        ApplicationBase(WindowContext* window);

        virtual void OnUpdate() override;
        virtual void OnImGuiRender() override;
        virtual bool IsAttached() override { return true; }

        void OnImGuiRenderOverlay();

        bool WindowShouldClose() const { return !m_IsWindowOpen; }
        bool HasWindowStateChanged() const { return m_WindowStateChange; }

    private:
        WindowedSettings InitializeWindowedSettings(const WindowContext* ctx);
        void HandleInput();

        void LayoutPreset(ImGuiID dockspaceID, ImVec2 dockSize);
        void ShowMenuBar();
        void ShowMainWindow();
        void ShowLogWindow();

    private:
        bool m_IsWindowOpen = true;
        bool m_F11Ready = true;
        bool m_WindowStateChange = false;

        WindowedSettings m_WindowedSettings;
    };

}
