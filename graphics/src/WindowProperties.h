#pragma once
#include <string>

#include "WindowMode.h"

namespace Graphics
{

    struct WindowProperties
    {
        WindowProperties(std::string title, unsigned int width, unsigned int height)
            : Title(title)
            , Width(width)
            , Height(height)
        {}

        std::string Title;
        unsigned int Width;
        unsigned int Height;

        WindowMode Mode = WindowMode::Windowed;
    };

}
