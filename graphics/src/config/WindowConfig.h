#pragma once

#include "ResolutionSetting.h"
#include "WindowProperties.h"

#include <vector>

namespace Graphics {

    struct WindowConfig
    {
        static WindowProperties Properties;
        static std::vector<ResolutionSetting> SupportedResolutions;
    };

}
