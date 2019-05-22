#pragma once

namespace Graphics {

    enum class EventType
    {
        Unknown = 0,
        ChangeResolutionEvent,
        ChangeToWindowedEvent,
        ChangeToFullscreenEvent,
        WindowCloseEvent,
        RenderTargetChanged
    };

}
