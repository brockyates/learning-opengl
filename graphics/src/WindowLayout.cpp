#include "pch.h"
#include "WindowLayout.h"

namespace Graphics {

    WindowLayout::WindowLayout(const int width, const int  height, const int  xPos, const int  yPos, const float aspectRatio)
        : Width(width)
        , Height(height)
        , XPos(xPos)
        , YPos(yPos)
        , WindowedAspectRatio(aspectRatio)
    {}

}
