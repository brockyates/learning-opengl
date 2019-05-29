#include "pch.h"
#include "WindowProperties.h"

namespace Graphics {

    WindowProperties::WindowProperties(std::string title, ResolutionSetting resolution, WindowMode windowMode, WindowLayout layout)
        : Title(title)
        , Resolution(resolution)
        , Mode(windowMode)
        , Layout(layout)
        , AspectRatio(static_cast<float>(resolution.Width) / static_cast<float>(resolution.Height))
    {}

}
