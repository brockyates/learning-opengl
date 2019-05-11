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
        ~Window();

        void OnUpdate();
        bool ShouldClose() const;

        unsigned int Width() const { return m_WindowProperties.Width; }
        unsigned int Height() const{ return m_WindowProperties.Height; }

    private:
        WindowMode GetNextWindowMode() const;
        void ShutdownCurrentContext();
        void StartWindowSystems();
        void EnterWindowed();
        void EnterFullscreen();

        void SetNextWindowMode();
        void DrawScene();
        void DrawUIElements();

    private:
        WindowProperties m_WindowProperties;
        SmartGLFWWindow m_Window;
        ImGuiRenderer m_UIRenderer;
        LayerManager m_Layers;
    };

}
