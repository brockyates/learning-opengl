#pragma once

#include "ResolutionSetting.h"
#include "WindowProperties.h"

#include <vector>

namespace Graphics {

    struct WindowConfig
    {
        static std::vector<ResolutionSetting> SupportedResolutions;
        static WindowProperties Properties;
    };

}
