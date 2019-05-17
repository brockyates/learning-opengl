#pragma once

#include "imgui/ImGuiRenderer.h"
#include "layers/LayerManager.h"

namespace Graphics {

    class Window
    {
    public:
        Window();
        ~Window();

        void OnUpdate();
        bool ShouldClose();

    private:
        void DrawScene();
        void DrawUIElements();

    private:
        WindowContext m_Context;
        ImGuiRenderer m_UIRenderer;
        LayerManager m_LayerManager;
    };

}
