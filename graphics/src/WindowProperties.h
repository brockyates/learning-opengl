#pragma once
#include <string>

#include "ResolutionSetting.h"
#include "WindowMode.h"
#include "WindowLayout.h"

namespace Graphics
{

    struct WindowProperties
    {
        WindowProperties(std::string title, ResolutionSetting resolution, WindowMode windowMode, WindowLayout layout)
            : Title(title)
            , Resolution(resolution)
            , Mode(windowMode)
            , Layout(layout)
            , AspectRatio(static_cast<float>(resolution.Width) / static_cast<float>(resolution.Height))
        {}

        std::string Title;
        ResolutionSetting Resolution;
        WindowMode Mode;
        WindowLayout Layout;
        float AspectRatio;
    };

}
