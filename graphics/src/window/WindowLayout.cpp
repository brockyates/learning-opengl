#include "pch.h"
#include "WindowLayout.h"

namespace Graphics
{
    WindowLayout::WindowLayout(const int32_t width, const int32_t  height, const int32_t  xPos, const int32_t  yPos, const float aspectRatio)
        : Width(width)
        , Height(height)
        , XPos(xPos)
        , YPos(yPos)
        , WindowedAspectRatio(aspectRatio)
    {}
}
