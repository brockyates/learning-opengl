#pragma once

#include "events/Event.h"

#include "layers/Layer.h"

#include <imgui.h>

namespace Graphics
{
    class Window;

    class BaseLayer final : public Layer
    {
    public:
        BaseLayer(const Window& window, EventHandler<Event> eventCallback);

        void RenderScene() override;
        void RenderUi() override;
        [[nodiscard]] bool IsAttached() const override { return true; }

        void OnImGuiRenderOverlay();

    private:
        void HandleInput();
        void HandleFullscreenInput();
        void HandleWindowedInput();

        static void LayoutPreset(ImGuiID dockspaceId, ImVec2 dockSize);
        void ShowMenuBar();
        void ShowMainWindow();
        void ShowLogWindow() const;

        //Input handling
        bool f11Ready_ = true;
        bool escReady_ = true;
    };
}
