#include "pch.h"
#include "LayerManager.h"

#include "WindowProperties.h"

#include "layers/Layer.h"
#include "layers/BaseUILayer.h"
#include "layers/HelloWorld.h"
#include "layers/HelloWorldFiddle.h"
#include "layers/RenderToTexture.h"

#include <imgui.h>

namespace Graphics {

    namespace {

        std::vector<std::unique_ptr<Layer>> MakeLayers(const WindowProperties& windowProperties)
        {
            std::vector<std::unique_ptr<Layer>> layers;

            //layers.emplace_back(std::make_unique<HelloWorld>(windowProperties));
            //layers.emplace_back(std::make_unique<HelloWorldFiddle>(windowProperties));
            layers.emplace_back(std::make_unique<RenderToTexture>(windowProperties));

            return layers;
        }
    }

    LayerManager::LayerManager(const WindowProperties& windowProperties, GLFWwindow* window)
        : m_Layers(MakeLayers(windowProperties))
        , m_BaseUILayer(window)
        , m_ActiveLayer(m_Layers.front().get())
    {
        m_ActiveLayer->Attach();
    }

    void LayerManager::OnUpdate()
    {
        m_BaseUILayer.OnUpdate();

        for (auto& layer : m_Layers)
        {
            layer->OnUpdate();
        }
    }

    void LayerManager::OnImGuiRender()
    {
        m_BaseUILayer.OnImGuiRender();

        ShowDemoSelector();

        for (auto& layer : m_Layers)
        {
            layer->OnImGuiRender();
        }
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
