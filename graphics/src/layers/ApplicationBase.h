#pragma once

#include "layers/Layer.h"

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
        void HandleInput();

        void LayoutPreset(ImGuiID dockspaceID, ImVec2 dockSize);
        void ShowMenuBar();
        void ShowMainWindow();
        void ShowLogWindow();

    private:
        bool m_F11Ready = true;
        bool m_WindowStateChange = false;
    };

}
