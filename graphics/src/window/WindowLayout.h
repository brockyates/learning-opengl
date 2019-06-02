#pragma once

namespace Graphics {

    struct WindowLayout
    {
        WindowLayout(int width, int  height, int  xPos, int  yPos, float aspectRatio);

        int Width;
        int Height;
        int XPos;
        int YPos;
        float WindowedAspectRatio;
    };

}
