#pragma once
#include "imgui/ImGuiRenderer.h"
#include "LayerManager.h"
#include "SmartGLFWWindow.h"
#include "WindowProperties.h"

namespace Graphics {

    struct WindowProperties;

    class Renderer
    {
    public:
        Renderer();

        void OnRender();
        bool IsRunning() const;

    private:
        void RenderScene();
        void RenderUIElements();

    private:
        WindowProperties m_WindowProperties;
        SmartGLFWWindow m_Window;
        ImGuiRenderer m_UIRenderer;
        LayerManager m_Layers;
    };

}
