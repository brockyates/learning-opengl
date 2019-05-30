#pragma once

#include <string>

namespace graphics {

    struct ResolutionSetting
    {
        ResolutionSetting(unsigned int width, unsigned int height, float defaultFontSize, std::string displayName)
            : Width(width)
            , Height(height)
            , DefaultFontSize(defaultFontSize)
            , DisplayName(displayName)
        {}

        bool operator==(const ResolutionSetting& other)
        {
            return Width == other.Width
                && Height == other.Height;
        }

        unsigned int Width;
        unsigned int Height;

        float DefaultFontSize; // I haven't implemented font-scaling in the GUI, so I try to pick an appropriate default size for each resolution.
        std::string DisplayName;
    };

}
