#pragma once
#include <string>

#include "ResolutionSetting.h"
#include "WindowMode.h"
#include "WindowLayout.h"

namespace Graphics
{

    struct WindowProperties
    {
        WindowProperties(std::string title, ResolutionSetting resolution, WindowMode windowMode, WindowLayout windowedProperties)
            : Title(title)
            , Resolution(resolution)
            , Mode(windowMode)
            , WindowedProperties(windowedProperties)
        {}

        std::string Title;
        ResolutionSetting Resolution;
        WindowMode Mode;
        WindowLayout WindowedProperties;

    };

}
