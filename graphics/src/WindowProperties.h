#pragma once
#include <string>

#include "ResolutionSetting.h"
#include "WindowMode.h"

namespace Graphics
{

    struct WindowProperties
    {
        WindowProperties(std::string title, ResolutionSetting resolution, WindowMode windowMode)
            : Title(title)
            , Resolution(resolution)
            , Mode(windowMode)
        {}

        std::string Title;
        ResolutionSetting Resolution;
        WindowMode Mode;
    };

}
