#pragma once
#include "layers/Layer.h"

#include "config/WindowConfig.h"

#include "WindowContext.h"
#include "WindowProperties.h"

#include <imgui.h>

namespace Graphics {

    class ApplicationBase : public Layer
    {
    public:
        ApplicationBase(const WindowContext* window);

        virtual void OnUpdate() override;
        virtual void OnImGuiRender() override;
        virtual bool IsAttached() override { return true; }

        bool WindowShouldClose() const { return !m_IsWindowOpen; }
        bool IsNewWindowRequired() const { return m_IsNewWindowRequired; }
        bool IsResolutionChangeRequired() const { return m_IsResolutionChangeRequired; }

        WindowProperties NextWindowProperties() const { return m_NextWindowProperties; }

    private:
        void HandleInput();

        void LayoutPreset(ImGuiID dockspaceID);
        void ShowMenuBar();
        void ShowMainWindow();
        void ShowLogWindow();
        void ShowGLWindow();
        void ShowDemoWidget();

    private:
        bool m_IsWindowOpen = true;
        bool m_IsNewWindowRequired = false;
        bool m_IsResolutionChangeRequired = false;

        WindowProperties m_NextWindowProperties = WindowConfig::Properties;
    };

}
