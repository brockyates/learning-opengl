#pragma once
#include "layers/Layer.h"

namespace Graphics {

    class BaseUILayer : public Layer
    {
    public:
        BaseUILayer();

        virtual void OnImGuiRender() override;
        virtual bool IsAttached() override { return true; }

        bool WindowShouldClose() const { return !m_IsWindowOpen; }

    private:
        void ShowMainWindow();
        void ShowLogWindow();
        void ShowGLWindow();
        void ShowDemoWidget();

    private:
        bool m_IsWindowOpen = true;
    };

}
