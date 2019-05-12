#include "pch.h"
#include "WindowConfig.h"
#include "WindowProperties.h"

namespace Graphics {

    WindowProperties WindowConfig::Properties{ "OpenGL Graphics Demo", 1920, 1080 };

    std::vector<ResolutionSetting> WindowConfig::SupportedResolutions =
    {
        {640,  480,  "640 x 480"},
        {800,  600,  "800 x 600"},
        {1024, 768,  "1024 x 768" },
        {1280, 720,  "1280 x 720 (720p)"},
        {1280, 800,  "1280 x 800"},
        {1366, 768,  "1366 x 768"},
        {1440, 900,  "1440 x 900"},
        {1600, 900,  "1600 x 900 (900p)"},
        {1600, 1200, "1600 x 1200"},
        {1920, 1080, "1920 x 1080 (1080p)"},
        {1920, 1200, "1920 x 1200"},
        {2560, 1440, "2560 x 1440"},
        {2560, 1600, "2560 x 1600"},
        {3840, 2160, "3840 x 2160 (4k)"}
    };

}
