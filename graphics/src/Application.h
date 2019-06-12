#pragma once

#include "layers/LayerManager.h"

#include <memory>

namespace Graphics
{
    class Application
    {
    public:
        Application();

        void Start();
        void OnEvent(const Event& event);

    private:
        std::unique_ptr<Window> window_;
        LayerManager layerManager_;
    };
}
