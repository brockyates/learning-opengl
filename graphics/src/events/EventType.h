#pragma once

namespace Graphics {

    enum class EventType
    {
        Unknown = 0,
        ResolutionChangeEvent,
        ChangeToWindowedEvent,
        ChangeToFullscreenEvent,
        WindowCloseEvent,
        RenderTargetChanged,
        AspectRatioChange
    };

}
