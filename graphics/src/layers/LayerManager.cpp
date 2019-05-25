#include "pch.h"
#include "LayerManager.h"

#include "layers/BaseLayer.h"
#include "layers/CircleDemo.h"
#include "layers/HelloWorld.h"
#include "layers/HelloWorldFiddle.h"
#include "layers/Layer.h"
#include "layers/PassthroughLayer.h"
#include "layers/RenderTargetLayer.h"

#include <imgui.h>

namespace Graphics {

    std::vector<std::unique_ptr<Layer>> LayerManager::MakeLayers(const Window& window, EventHandler<Event> eventCallback)
    {
        std::vector<std::unique_ptr<Layer>> layers;
        layers.emplace_back(std::make_unique<HelloWorld>(window, eventCallback));
        layers.emplace_back(std::make_unique<HelloWorldFiddle>(window, eventCallback));
        layers.emplace_back(std::make_unique<CircleDemo>(window, eventCallback));

        return layers;
    }

    LayerManager::LayerManager(const Window& window, EventHandler<Event> eventCallback)
        : m_Layers(MakeLayers(window, eventCallback))
        , m_BaseLayer(window, eventCallback)
        , m_RenderTarget(window, eventCallback)
        , m_ActiveLayer(m_Layers[2].get())
        , m_UIRenderer(window)
    {
        m_ActiveLayer->Attach();
    }

    void LayerManager::RenderScene()
    {
        m_BaseLayer.RenderScene();
        m_RenderTarget.RenderScene();

        m_ActiveLayer->RenderScene();
    }

    void LayerManager::RenderUI()
    {
        m_UIRenderer.BeginFrame();
        m_BaseLayer.RenderUI();
        m_RenderTarget.RenderUI();
        ShowDemoSelector();

        m_ActiveLayer->RenderUI();

        m_BaseLayer.OnImGuiRenderOverlay();
        m_UIRenderer.Render();
    }

    void LayerManager::OnEvent(const Event& event)
    {
        m_BaseLayer.OnEvent(event);
        m_RenderTarget.OnEvent(event);

        for (auto& layer : m_Layers)
        {
            layer->OnEvent(event);
        }
    }

    void LayerManager::ShowDemoSelector()
    {
        ImGui::Begin("DemoWidget");

        if (ImGui::BeginCombo("Scene", m_ActiveLayer->Name().c_str()))
        {
            for (auto& layer : m_Layers)
            {
                bool isSelected = (m_ActiveLayer == layer.get());

                if (ImGui::Selectable(layer->Name().c_str(), isSelected))
                {
                    UpdateActiveLayer(layer.get());
                }

                if (ImGui::IsItemHovered())
                {
                    ImGui::SetTooltip(layer->PopupText().c_str());
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

        m_ActiveLayer->Detach();
        m_ActiveLayer = nextActiveLayer;
        m_ActiveLayer->Attach();
    }

}
