#include "pch.h"
#include "LayerManager.h"

#include "layers/Layer.h"
#include "layers/BaseUILayer.h"
#include "layers/MinimalRenderDemo.h"
#include "layers/TestLayer.h"

#include <imgui.h>

namespace Graphics {

    namespace {

        std::vector<std::unique_ptr<Layer>> MakeLayers()
        {
            std::vector<std::unique_ptr<Layer>> layers;

            layers.emplace_back(std::make_unique<MinimalRenderDemo>());
            layers.emplace_back(std::make_unique<TestLayer>());

            return layers;
        }
    }

    LayerManager::LayerManager(GLFWwindow* window)
        : m_Layers(MakeLayers())
        , m_BaseUILayer(window)
    {
        m_Layers[0]->Attach();
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

        static Layer* item_current = m_Layers[0].get();

        if (ImGui::BeginCombo("Demo", item_current->GetName().c_str()))
        {
            for (int n = 0; n < std::size(m_Layers); n++)
            {
                bool is_selected = (item_current == m_Layers[n].get());

                if (ImGui::Selectable(m_Layers[n]->GetName().c_str(), is_selected))
                {
                    item_current = m_Layers[n].get();
                }

                if (is_selected)
                {
                    ImGui::SetItemDefaultFocus();
                }
            }
            ImGui::EndCombo();
        }

        if (!item_current->IsAttached())
        {
            for (auto& layer : m_Layers)
            {
                layer->Detach();
            }

            item_current->Attach();
        }

        ImGui::End();
    }

}
