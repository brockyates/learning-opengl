#pragma once

#include "imgui/ImGuiRenderer.h"
#include "layers/SceneManager.h"

namespace Graphics {

    class Window
    {
    public:
        Window();
        ~Window();

        void Update();

        bool ShouldClose();
        bool IsFullscreen() const;

        WindowContext* Context() { return &m_Context; }

    private:
        WindowContext m_Context;
    };

}
