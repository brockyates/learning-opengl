#pragma once
#include "layers/Layer.h"

#include "WindowContext.h"

namespace Graphics {

    class BaseUILayer : public Layer
    {
    public:
        BaseUILayer(const WindowContext* window);

        virtual void OnUpdate() override;
        virtual void OnImGuiRender() override;
        virtual bool IsAttached() override { return true; }

        bool WindowShouldClose() const { return !m_IsWindowOpen; }
        WindowMode NextWindowMode() const { return m_NextWindowMode; }

        void OnWindowStateChange(const WindowContext* window);

    private:
        void HandleInput();
        void ShowMainWindow();
        void ShowLogWindow();
        void ShowGLWindow();
        void ShowDemoWidget();

    private:
        WindowMode m_NextWindowMode = WindowMode::Windowed;

        bool m_IsWindowOpen = true;

        const WindowContext* m_Window;
    };

}
