#pragma once

#include "EventType.h"
namespace Graphics {

    template <typename T>
    using EventHandler = std::function<void(const T&)>;

    class Event
    {
    public:
        virtual EventType Type() const = 0;
    };

}
