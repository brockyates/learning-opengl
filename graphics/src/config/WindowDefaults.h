#pragma once

#include "ResolutionSetting.h"
#include "WindowProperties.h"

#include <vector>

namespace graphics {

    struct WindowDefaults
    {
        static std::vector<ResolutionSetting> SupportedResolutions;
        static WindowProperties Properties;
    };

}
