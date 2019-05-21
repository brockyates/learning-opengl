#include "pch.h"
#include "WindowDefaults.h"

namespace Graphics {

    std::vector<ResolutionSetting> WindowDefaults::SupportedResolutions =
    {
        {800,  600,  10.0f,   "800 x 600"},              // 0
        {1024, 768,  10.0f,   "1024 x 768" },            // 1
        {1280, 720,  10.0f,   "1280 x 720 (720p)"},      // 2
        {1280, 800,  10.0f,   "1280 x 800"},             // 3
        {1366, 768,  12.0f,   "1366 x 768"},             // 4
        {1600, 900,  14.0f,   "1600 x 900 (900p)"},      // 5
        {1600, 1200, 14.0f,   "1600 x 1200"},            // 6
        {1920, 1080, 14.0f,   "1920 x 1080 (1080p)"},    // 7
        {1920, 1200, 14.0f,   "1920 x 1200"},            // 8
        {2560, 1440, 20.0f,   "2560 x 1440"},            // 9
        {2560, 1600, 20.0f,   "2560 x 1600"},            // 10
        {3840, 2160, 24.0f,   "3840 x 2160 (4k)"}        // 11
    };

    WindowProperties WindowDefaults::Properties{
        "OpenGL Graphics Demo",
        WindowDefaults::SupportedResolutions[2], /* 720p as safe default resolution */
        WindowMode::Windowed,
        WindowLayout(1280, 720, 0, 0)
    };

}
