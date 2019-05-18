#include "pch.h"
#include "SceneManager.h"

#include "layers/ApplicationBase.h"
#include "layers/Layer.h"
#include "layers/RenderToTexture.h"

#include <imgui.h>

namespace Graphics {

    namespace {

        std::vector<std::unique_ptr<Layer>> MakeLayers(Window* window)
        {
            std::vector<std::unique_ptr<Layer>> layers;

            layers.emplace_back(std::make_unique<RenderToTexture>(window));

            return layers;
        }
    }

    SceneManager::SceneManager(Window* window)
        : m_SceneManager(MakeLayers(window))
        , m_ApplicationBase(window)
        , m_ActiveLayer(m_SceneManager.front().get())
        , m_UIRenderer(window)
    {
        m_ActiveLayer->Attach();
    }

    void SceneManager::RenderScene()
    {
        if (m_ApplicationBase.HasSceneResolutionChanged())
        {
            m_ActiveLayer->Detach();
            m_ActiveLayer->Attach();
        }

        m_ApplicationBase.RenderScene();

        m_ActiveLayer->RenderScene();
    }

    void SceneManager::RenderUI()
    {
        m_UIRenderer.BeginFrame();
        m_ApplicationBase.RenderUI();

        ShowDemoSelector();

        for (auto& layer : m_SceneManager)
        {
            layer->RenderUI();
        }

        m_ApplicationBase.OnImGuiRenderOverlay();

        m_UIRenderer.Render();
    }

    void SceneManager::ShowDemoSelector()
    {
        ImGui::Begin("DemoWidget");

        if (ImGui::BeginCombo("Scene", m_ActiveLayer->GetName().c_str()))
        {
            for (auto& layer : m_SceneManager)
            {
                bool isSelected = (m_ActiveLayer == layer.get());

                if (ImGui::Selectable(layer->GetName().c_str(), isSelected))
                {
                    UpdateActiveLayer(layer.get());
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

        ImGui::End();
    }

    void SceneManager::UpdateActiveLayer(Layer* nextActiveLayer)
    {
        if (nextActiveLayer->IsAttached())
            return;

        m_ActiveLayer->Detach();
        m_ActiveLayer = nextActiveLayer;
        m_ActiveLayer->Attach();
    }

}
