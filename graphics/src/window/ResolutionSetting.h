#pragma once

#include <string>
#include <utility>

namespace Graphics
{
    struct ResolutionSetting
    {
        ResolutionSetting(const int32_t width, const int32_t height, const float defaultFontSize, std::string displayName)
            : Width(width)
            , Height(height)
            , DefaultFontSize(defaultFontSize)
            , DisplayName(std::move(displayName))
        {}

        bool operator==(const ResolutionSetting& other) const
        {
            return Width == other.Width
                && Height == other.Height;
        }

        int32_t Width;
        int32_t Height;

        float DefaultFontSize; // I haven't implemented font-scaling in the GUI, so I try to pick an appropriate default size for each resolution.
        std::string DisplayName;
    };
}
