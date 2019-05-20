#pragma once

#include "events/ChangeResolutionEvent.h"
#include "events/ChangeToWindowedEvent.h"
#include "events/Event.h"
#include "layers/Layer.h"

#include <imgui.h>

namespace Graphics {

    class ApplicationBase : public Layer
    {
    public:
        ApplicationBase(Window* window, EventHandler<Event> eventCallback);

        virtual void RenderScene() override;
        virtual void RenderUI() override;
        virtual bool IsAttached() override { return true; }

        virtual void OnEvent(Event& event) override;

        void OnImGuiRenderOverlay();

    private:
        //Event handlers
        EventHandler<ChangeResolutionEvent> OnResolutionChange();

        void HandleInput();
        void LayoutPreset(ImGuiID dockspaceID, ImVec2 dockSize);
        void ShowMenuBar();
        void ShowMainWindow();
        void ShowLogWindow();

    private:
        bool m_F11Ready = true;
    };

}
