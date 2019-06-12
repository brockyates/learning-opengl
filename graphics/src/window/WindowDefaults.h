#pragma once

#include "window/ResolutionSetting.h"
#include "WindowProperties.h"

#include <vector>

namespace Graphics
{
    struct WindowDefaults
    {
        static std::vector<ResolutionSetting> SupportedResolutions;
        static WindowProperties Properties;
    };
}
