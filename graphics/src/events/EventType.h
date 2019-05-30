#pragma once

namespace graphics {

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
