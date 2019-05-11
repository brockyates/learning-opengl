#pragma once
#include "layers/Layer.h"

#include "Input.h"

namespace Graphics {

    class BaseUILayer : public Layer
    {
    public:
        BaseUILayer(GLFWwindow* window);

        virtual void OnUpdate() override;
        virtual void OnImGuiRender() override;
        virtual bool IsAttached() override { return true; }

        bool WindowShouldClose() const { return !m_IsWindowOpen; }
        bool UIIsEnabled() const { return m_IsUIEnabled; }

        void OnWindowStateChange(GLFWwindow* window);

    private:
        void HandleInput();
        void ShowMainWindow();
        void ShowLogWindow();
        void ShowGLWindow();
        void ShowDemoWidget();

    private:
        Input m_Input;

        bool m_IsWindowOpen = true;
        bool m_IsUIEnabled = true;
        GLFWwindow* m_Window;
    };

}
