#pragma once

#include "WindowContext.h"

namespace Graphics {

    class Window
    {
    public:
        Window();
        ~Window();

        void Update();

        bool ShouldClose();
        bool IsFullscreen() const;

        int Width() const { return m_Context.Properties.Resolution.Width; }
        int Height() const { return m_Context.Properties.Resolution.Height; }

        WindowContext* Context() { return &m_Context; }

    private:
        WindowContext m_Context;
    };

}
