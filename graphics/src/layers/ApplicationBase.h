#pragma once
#include "layers/Layer.h"

#include "WindowContext.h"
#include "ResolutionSetting.h"

namespace Graphics {

    class ApplicationBase : public Layer
    {
    public:
        ApplicationBase(const WindowContext* window);

        virtual void OnUpdate() override;
        virtual void OnImGuiRender() override;
        virtual bool IsAttached() override { return true; }

        bool WindowShouldClose() const { return !m_IsWindowOpen; }
        bool IsNewWindowRequired() const { return m_IsNewWindowRequired; }
        bool IsResolutionChangeRequired() const { return m_IsResolutionChangeRequired; }

        WindowMode NextWindowMode() const { return m_NextWindowMode; }

    private:
        void HandleInput();
        void ShowMainWindow();
        void ShowLogWindow();
        void ShowGLWindow();
        void ShowDemoWidget();

    private:
        bool m_IsWindowOpen = true;
        bool m_IsNewWindowRequired = false;
        bool m_IsResolutionChangeRequired = false;

        WindowMode m_NextWindowMode = WindowMode::Windowed;
        ResolutionSetting m_FullscreenResolution = { 1920, 1080, "1920 x 1080 (1080p)" };
    };

}
