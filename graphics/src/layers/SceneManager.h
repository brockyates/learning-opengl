#pragma once

#include "ApplicationBase.h"
#include "imgui/ImGuiRenderer.h"
#include "Layer.h"
#include "Window.h"

namespace Graphics {

    class Layer;
    struct WindowProperties;

    class SceneManager
    {
    public:
        SceneManager(Window* window);
        ~SceneManager() = default;

        SceneManager(SceneManager&&) = default;
        SceneManager& operator=(SceneManager&&) = default;

        void RenderScene(Window* window);
        void RenderUI(Window* window);

    private:
        void ShowDemoSelector(Window* window);
        void UpdateActiveLayer(Window* window, Layer* activeLayer);

    private:
        ApplicationBase m_ApplicationBase;

        std::vector<std::unique_ptr<Layer>> m_SceneManager;
        Layer* m_ActiveLayer;

        ImGuiRenderer m_UIRenderer;
    };

}
