#pragma once
#include "renderer/Layer.h"

namespace Graphics {

    class BaseUILayer : public Layer
    {
    public:
        BaseUILayer(GLFWwindow* window);
        virtual void OnImGuiRender() override;

    private:
        void CloseApplication() const;
        void ShowMainWindow();
        void ShowLogWindow();

    private:
        GLFWwindow* m_Window;
        bool m_IsWindowOpen = true;
    };

}
