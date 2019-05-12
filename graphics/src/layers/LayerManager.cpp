#include "pch.h"
#include "LayerManager.h"

#include "WindowContext.h"

#include "layers/Layer.h"
#include "layers/ApplicationBase.h"
#include "layers/RenderToTexture.h"

#include <imgui.h>

namespace Graphics {

    namespace {

        std::vector<std::unique_ptr<Layer>> MakeLayers(const WindowContext* window)
        {
            std::vector<std::unique_ptr<Layer>> layers;

            layers.emplace_back(std::make_unique<RenderToTexture>(window));

            return layers;
        }
    }

    LayerManager::LayerManager(const WindowContext* window)
        : m_Window(window)
        , m_Layers(MakeLayers(window))
        , m_ApplicationBase(window)
        , m_ActiveLayer(m_Layers.front().get())
    {
        m_ActiveLayer->Attach();
    }

    void LayerManager::OnUpdate()
    {
        m_ApplicationBase.OnUpdate();

        for (auto& layer : m_Layers)
        {
            layer->OnUpdate();
        }
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
    }

    void LayerManager::OnWindowStateChange(const WindowContext* window)
    {
        m_ApplicationBase.ChangeContext(window);
       
        for (auto& layer : m_Layers)
        {
            layer->ChangeContext(window);
        }

        m_ActiveLayer->Detach();
        m_ActiveLayer->Attach();

    }

    void LayerManager::ShowDemoSelector()
    {
        ImGui::Begin("Demos");

        Layer* nextActiveLayer = m_ActiveLayer;

        if (ImGui::BeginCombo("Active Scene", m_ActiveLayer->GetName().c_str()))
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
