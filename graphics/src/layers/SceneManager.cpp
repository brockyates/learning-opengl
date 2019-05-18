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

            layers.emplace_back(std::make_unique<RenderToTexture>());

            return layers;
        }
    }

    SceneManager::SceneManager(Window* window)
        : m_SceneManager(MakeLayers(window))
        , m_ApplicationBase(window)
        , m_ActiveLayer(m_SceneManager.front().get())
        , m_UIRenderer(window)
    {
        m_ActiveLayer->Attach(window);
    }

    void SceneManager::RenderScene(Window* window)
    {
        if (m_ApplicationBase.HasSceneResolutionChanged())
        {
            m_ActiveLayer->Detach(window);
            m_ActiveLayer->Attach(window);
        }

        m_ApplicationBase.RenderScene(window);

        m_ActiveLayer->RenderScene(window);
    }

    void SceneManager::RenderUI(Window* window)
    {
        m_UIRenderer.BeginFrame();

        m_ApplicationBase.RenderUI(window);

        //if (m_Window->Properties.Mode == WindowMode::Fullscreen) return;

        ShowDemoSelector(window);

        for (auto& layer : m_SceneManager)
        {
            layer->RenderUI(window);
        }

        m_ApplicationBase.OnImGuiRenderOverlay(window);

        m_UIRenderer.Render(window);
    }

    void SceneManager::ShowDemoSelector(Window* window)
    {
        ImGui::Begin("DemoWidget");

        Layer* nextActiveLayer = m_ActiveLayer;

        if (ImGui::BeginCombo("Scene", m_ActiveLayer->GetName().c_str()))
        {
            for (auto& layer : m_SceneManager)
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

        UpdateActiveLayer(window, nextActiveLayer);

        ImGui::End();
    }

    void SceneManager::UpdateActiveLayer(Window* window, Layer* nextActiveLayer)
    {
        if (nextActiveLayer->IsAttached())
            return;

        m_ActiveLayer->Detach(window);
        m_ActiveLayer = nextActiveLayer;
        m_ActiveLayer->Attach(window);
    }

}
