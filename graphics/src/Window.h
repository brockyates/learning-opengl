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
        WindowContext m_Context;
        ImGuiRenderer m_UIRenderer;
        LayerManager m_LayerManager;
    };

}
