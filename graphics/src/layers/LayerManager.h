#pragma once

#include "events/Event.h"

#include "BaseLayer.h"
#include "RenderTargetLayer.h"

#include "imgui/ImGuiRenderer.h"

namespace Graphics
{
    class Window;

    class LayerManager
    {
    public:
        LayerManager(const Window& window, const EventHandler<Event>& eventCallback);

        void RenderScene();
        void RenderUi();
        void OnEvent(const Event& event);

    private:
        [[nodiscard]] std::vector<std::unique_ptr<Layer>> MakeLayers(const Window& window,
                                                       const EventHandler<Event>& eventCallback) const;
        void ShowDemoSelector();
        void UpdateActiveLayer(Layer* nextActiveLayer);

    private:
        std::vector<std::unique_ptr<Layer>> layers_;
        BaseLayer baseLayer_;
        RenderTargetLayer renderTarget_;

        Layer* activeLayer_;
        ImGuiRenderer uiRenderer_;
    };
}
