#include "pch.h"
#include "LayerManager.h"

#include "layers/BaseLayer.h"
#include "layers/CircleDemo.h"
#include "layers/HelloWorld.h"
#include "layers/HelloWorldFiddle.h"
#include "layers/Layer.h"
#include "layers/RenderTargetLayer.h"

#include "window/Window.h"

#include <imgui.h>

#include <memory>
#include <vector>

namespace Graphics
{
    std::vector<std::unique_ptr<Layer>> LayerManager::MakeLayers(const Window& window,
                                                                 const EventHandler<Event>& eventCallback) const
    {
        std::vector<std::unique_ptr<Layer>> layers;
        layers.emplace_back(std::make_unique<HelloWorld>(window, eventCallback));
        layers.emplace_back(std::make_unique<CircleDemo>(window, eventCallback));
        layers.emplace_back(std::make_unique<HelloWorldFiddle>(window, eventCallback));

        return layers;
    }

    LayerManager::LayerManager(const Window& window, const EventHandler<Event>& eventCallback)
        : layers_(MakeLayers(window, eventCallback))
          , baseLayer_(window, eventCallback)
          , renderTarget_(window, eventCallback)
          , activeLayer_(layers_[2].get())
          , uiRenderer_(window)
    {
        activeLayer_->Attach();
    }

    void LayerManager::RenderScene()
    {
        baseLayer_.RenderScene();
        renderTarget_.RenderScene();

        activeLayer_->RenderScene();
    }

    void LayerManager::RenderUi()
    {
        ImGuiRenderer::BeginFrame();
        baseLayer_.RenderUi();
        renderTarget_.RenderUi();
        ShowDemoSelector();

        activeLayer_->RenderUi();

        baseLayer_.OnImGuiRenderOverlay();
        uiRenderer_.Render();
    }

    void LayerManager::OnEvent(const Event& event)
    {
        baseLayer_.OnEvent(event);
        renderTarget_.OnEvent(event);

        for (auto& layer : layers_)
        {
            layer->OnEvent(event);
        }
    }

    void LayerManager::ShowDemoSelector()
    {
        ImGui::Begin("DemoWidget");

        if (ImGui::BeginCombo("Scene", activeLayer_->Name().c_str()))
        {
            for (auto& layer : layers_)
            {
                const auto isSelected = activeLayer_ == layer.get();

                if (ImGui::Selectable(layer->Name().c_str(), isSelected))
                {
                    UpdateActiveLayer(layer.get());
                }

                if (ImGui::IsItemHovered())
                {
                    ImGui::SetTooltip("%s", layer->PopupText().c_str());
                }

                if (isSelected)
                {
                    ImGui::SetItemDefaultFocus();
                }
            }

            ImGui::EndCombo();
        }

        ImGui::End();
    }

    void LayerManager::UpdateActiveLayer(Layer* nextActiveLayer)
    {
        if (nextActiveLayer->IsAttached())
            return;

        activeLayer_->Detach();
        activeLayer_ = nextActiveLayer;
        activeLayer_->Attach();
    }
}
