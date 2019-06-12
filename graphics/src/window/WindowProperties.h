#pragma once

#include "window/ResolutionSetting.h"
#include "WindowMode.h"
#include "WindowLayout.h"

#include <string>

namespace Graphics
{
    struct WindowProperties
    {
        WindowProperties(std::string title, const ResolutionSetting& resolution, WindowMode windowMode, WindowLayout layout);

        std::string Title;
        ResolutionSetting Resolution;
        WindowMode Mode;
        WindowLayout Layout;
        float AspectRatio;
    };
}
