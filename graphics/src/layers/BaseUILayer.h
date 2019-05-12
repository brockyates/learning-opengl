#pragma once
#include "layers/Layer.h"

#include "WindowInput.h"
#include "WindowMode.h"
#include "WindowProperties.h"

namespace Graphics {

    class BaseUILayer : public Layer
    {
    public:
        BaseUILayer(GLFWwindow* window, const WindowProperties& windowProperties);

        virtual void OnUpdate() override;
        virtual void OnImGuiRender() override;
        virtual bool IsAttached() override { return true; }

        bool WindowShouldClose() const { return !m_IsWindowOpen; }
        WindowMode NextWindowMode() const { return m_NextWindowMode; }

        void OnWindowStateChange(GLFWwindow* window);

    private:
        void HandleInput();
        void ShowMainWindow();
        void ShowLogWindow();
        void ShowGLWindow();
        void ShowDemoWidget();

    private:
        WindowInput m_Input;
        WindowMode m_NextWindowMode = WindowMode::Windowed;

        bool m_IsWindowOpen = true;

        const WindowProperties& m_WindowProperties;
    };

}
