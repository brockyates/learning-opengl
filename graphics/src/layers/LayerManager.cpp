#include "pch.h"
#include "LayerManager.h"

#include "WindowContext.h"

#include "layers/Layer.h"
#include "layers/ApplicationBase.h"
#include "layers/RenderToTexture.h"

#include <imgui.h>

namespace Graphics {

    namespace {

        std::vector<std::unique_ptr<Layer>> MakeLayers(WindowContext* window)
        {
            std::vector<std::unique_ptr<Layer>> layers;

            layers.emplace_back(std::make_unique<RenderToTexture>(window));

            return layers;
        }
    }

    LayerManager::LayerManager(WindowContext* window)
        : m_Window(window)
        , m_Layers(MakeLayers(window))
        , m_ApplicationBase(window)
        , m_ActiveLayer(m_Layers.front().get())
    {
        m_ActiveLayer->Attach();
    }

    void LayerManager::OnUpdate()
    {
        if (m_ApplicationBase.HasSceneResolutionChanged())
        {
            m_ActiveLayer->Detach();
            m_ActiveLayer->Attach();
        }

        m_ApplicationBase.OnUpdate();

        m_ActiveLayer->OnUpdate();
    }

    void LayerManager::OnImGuiRender()
    {
        m_ApplicationBase.OnImGuiRender();

        if (m_Window->Properties.Mode == WindowMode::Fullscreen)
            return;

        ShowDemoSelector();

        for (auto& layer : m_Layers)
        {
            layer->OnImGuiRender();
        }

        m_ApplicationBase.OnImGuiRenderOverlay();
    }

    void LayerManager::ShowDemoSelector()
    {
        ImGui::Begin("DemoWidget");

        Layer* nextActiveLayer = m_ActiveLayer;

        if (ImGui::BeginCombo("Scene", m_ActiveLayer->GetName().c_str()))
        {
            for (auto& layer : m_Layers)
            {
                bool isSelected = (m_ActiveLayer == layer.get());

                if (ImGui::Selectable(layer->GetName().c_str(), isSelected))
                {
                    nextActiveLayer = layer.get();
                }

                if (ImGui::IsItemHovered())
                {
                    ImGui::SetTooltip(layer->GetPopupText().c_str());
                }

                if (isSelected)
                {
                    ImGui::SetItemDefaultFocus();
                }
            }

            ImGui::EndCombo();
        }

        UpdateActiveLayer(nextActiveLayer);

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
