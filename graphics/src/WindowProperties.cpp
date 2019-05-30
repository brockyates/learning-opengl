#include "pch.h"
#include "WindowProperties.h"
#include <utility>

namespace Graphics {

    WindowProperties::WindowProperties(std::string title, const ResolutionSetting& resolution, WindowMode windowMode, WindowLayout layout)
        : Title(std::move(title))
        , Resolution(resolution)
        , Mode(windowMode)
        , Layout(layout)
        , AspectRatio(static_cast<float>(resolution.Width) / static_cast<float>(resolution.Height))
    {}

}
