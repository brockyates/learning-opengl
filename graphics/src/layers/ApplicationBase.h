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
        ApplicationBase(const WindowContext* window);

        virtual void OnUpdate() override;
        virtual void OnImGuiRender() override;
        virtual bool IsAttached() override { return true; }

        void OnImGuiRenderOverlay();

        bool WindowShouldClose() const { return !m_IsWindowOpen; }
        bool IsNewWindowRequired() const { return m_IsNewWindowRequired; }
        bool IsResolutionChangeRequired() const { return m_IsResolutionChangeRequired; }

        WindowProperties NextWindowProperties() const { return m_NextWindowProperties; }
        WindowedSettings GetWindowedSettings() const { return m_WindowedSettings; }

    private:
        WindowedSettings InitializeWindowedSettings(const WindowContext* ctx);
        void HandleInput();

        void LayoutPreset(ImGuiID dockspaceID, ImVec2 dockSize);
        void ShowMenuBar();
        void ShowMainWindow();
        void ShowLogWindow();

    private:
        bool m_IsWindowOpen = true;
        bool m_IsNewWindowRequired = false;
        bool m_IsResolutionChangeRequired = false;
        bool m_F11Ready = true;

        WindowProperties m_NextWindowProperties = WindowConfig::Properties;
        WindowedSettings m_WindowedSettings;
    };

}
