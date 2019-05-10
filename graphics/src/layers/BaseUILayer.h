#pragma once
#include "layers/Layer.h"

namespace Graphics {

    class BaseUILayer : public Layer
    {
    public:
        BaseUILayer(GLFWwindow* window);
        virtual void OnImGuiRender() override;

        virtual bool IsAttached() override { return true; }

    private:
        void CloseApplication() const;
        void ShowMainWindow();
        void ShowLogWindow();
        void ShowGLWindow();
        void ShowDemoWidget();

    private:
        GLFWwindow* m_Window;
        bool m_IsWindowOpen = true;
    };

}
