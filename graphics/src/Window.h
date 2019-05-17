#pragma once

#include "layers/LayerManager.h"
#include "SmartGLFWWindow.h"

#include "imgui/ImGuiRenderer.h"

namespace Graphics {

    class Window
    {
    public:
        Window();
        ~Window();

        void OnUpdate();
        bool ShouldClose() const;

    private:
        void DrawScene();
        void DrawUIElements();

    private:
        SmartGLFWWindow m_Window;
        std::unique_ptr<WindowContext> m_WindowContext = nullptr;
        ImGuiRenderer m_UIRenderer;
        LayerManager m_LayerManager;
    };

}
