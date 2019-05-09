#pragma once
#include "imgui/ImGuiRenderer.h"
#include "SmartGLFWWindow.h"
#include "WindowProperties.h"

#include "layers/LayerManager.h"

namespace Graphics {

    struct WindowProperties;

    class Window
    {
    public:
        Window();

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
