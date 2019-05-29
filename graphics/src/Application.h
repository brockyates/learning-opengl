#pragma once

#include "layers/LayerManager.h"
#include "Window.h"

#include <memory>

namespace Graphics
{

    class Application
    {
    public:
        Application();
        ~Application() = default;

        void Start();
        void OnEvent(const Event& event);

    private:
        std::unique_ptr<Window> m_Window;
        LayerManager m_LayerManager;
    };

}
