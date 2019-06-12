#pragma once

namespace Graphics {

    enum class EventType
    {
        Unknown = 0,
        ResolutionEvent,
        WindowedEvent,
        FullscreenEvent,
        WindowCloseEvent,
        RenderTargetEvent,
        AspectRatioEvent
    };

}
