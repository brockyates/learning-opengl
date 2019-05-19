#pragma once

#include "events/Event.h"
#include "layers/SceneManager.h"
#include "Window.h"

namespace Graphics
{

    class Application
    {
    public:
        Application();
        ~Application() = default;

        void Start();
        void OnEvent(Event& event);

    private:
        std::unique_ptr<Window> m_Window;
        SceneManager m_SceneManager;
    };

}
