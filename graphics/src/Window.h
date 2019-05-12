#pragma once

#include "SmartGLFWWindow.h"

#include "layers/LayerManager.h"

#include "imgui/ImGuiRenderer.h"

namespace Graphics {

    class Window
    {
    public:
        Window();
        ~Window();

        void OnUpdate();
        bool ShouldClose() const;

        unsigned int Width() const { return m_WindowContext->Properties.Width; }
        unsigned int Height() const{ return m_WindowContext->Properties.Height; }

    private:
        void SetNextWindowMode();
        void ShutdownCurrentContext();
        void StartWindowSystems();
        void EnterWindowed();
        void EnterFullscreen();

        void DrawScene();
        void DrawUIElements();

    private:
        SmartGLFWWindow m_Window;
        std::unique_ptr<WindowContext> m_WindowContext = nullptr;
        ImGuiRenderer m_UIRenderer;
        LayerManager m_Layers;
    };

}
