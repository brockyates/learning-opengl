#pragma once
#include <string>

#include "ResolutionSetting.h"
#include "WindowMode.h"
#include "WindowedSetting.h"

namespace Graphics
{

    struct WindowProperties
    {
        WindowProperties(std::string title, ResolutionSetting resolution, WindowMode windowMode, WindowedSetting windowedProperties)
            : Title(title)
            , Resolution(resolution)
            , Mode(windowMode)
            , WindowedProperties(windowedProperties)
        {}

        std::string Title;
        ResolutionSetting Resolution;
        WindowMode Mode;
        WindowedSetting WindowedProperties;

    };

}
