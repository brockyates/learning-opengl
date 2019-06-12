#pragma once

namespace Graphics
{
    struct WindowLayout
    {
        WindowLayout(int32_t width, int32_t  height, int32_t  xPos, int32_t  yPos, float aspectRatio);

        int32_t Width;
        int32_t Height;
        int32_t XPos;
        int32_t YPos;
        float WindowedAspectRatio;
    };
}
