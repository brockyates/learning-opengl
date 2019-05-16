#include "pch.h"
#include "WindowConfig.h"
#include "WindowProperties.h"

namespace Graphics {

    std::vector<ResolutionSetting> WindowConfig::SupportedResolutions =
    {
        {640,  480,  10.0f,   "640 x 480"},              // 0
        {800,  600,  10.0f,   "800 x 600"},              // 1
        {1024, 768,  10.0f,   "1024 x 768" },            // 2
        {1280, 720,  10.0f,   "1280 x 720 (720p)"},      // 3
        {1280, 800,  10.0f,   "1280 x 800"},             // 4
        {1366, 768,  12.0f,   "1366 x 768"},             // 5
        {1440, 900,  12.0f,   "1440 x 900"},             // 6
        {1600, 900,  14.0f,   "1600 x 900 (900p)"},      // 7
        {1600, 1200, 14.0f,   "1600 x 1200"},            // 8
        {1920, 1080, 14.0f,   "1920 x 1080 (1080p)"},    // 9
        {1920, 1200, 14.0f,   "1920 x 1200"},            // 10
        {2560, 1440, 20.0f,   "2560 x 1440"},            // 11
        {2560, 1600, 20.0f,   "2560 x 1600"},            // 12
        {3840, 2160, 24.0f,   "3840 x 2160 (4k)"}        // 13
    };

    WindowProperties WindowConfig::Properties{
        "OpenGL Graphics Demo",
        WindowConfig::SupportedResolutions[3], /* 720p as safe default resolution */
        WindowMode::Windowed
    };

}
