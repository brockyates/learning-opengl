#pragma once

#include "events/EventSystem.h"
#include "layers/Layer.h"

#include <imgui.h>

namespace Graphics {

    class BaseLayer : public Layer
    {
    public:
        BaseLayer(const Window& window, EventHandler<Event> eventCallback);

        virtual void RenderScene() override;
        virtual void RenderUI() override;
        virtual bool IsAttached() const override { return true; }

        void OnImGuiRenderOverlay();

    private:
        void HandleInput();
        void LayoutPreset(ImGuiID dockspaceID, ImVec2 dockSize);
        void ShowMenuBar();
        void ShowMainWindow();
        void ShowLogWindow();

    private:
        bool m_F11Ready = true;
    };

}
