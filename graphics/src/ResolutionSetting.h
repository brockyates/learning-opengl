#pragma once

#include <string>

namespace Graphics {

    struct ResolutionSetting
    {
        ResolutionSetting(unsigned int width, unsigned int height, std::string displayName)
            : Width(width)
            , Height(height)
            , DisplayName(displayName)
        {}

        bool operator==(const ResolutionSetting& other)
        {
            return Width == other.Width
                && Height == other.Height;
        }

        unsigned int Width;
        unsigned int Height;

        std::string DisplayName;
    };

}
