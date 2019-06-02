#pragma once

#include <functional>

namespace Graphics {

    enum class EventType;

    template <typename T>
    using EventHandler = std::function<void(const T&)>;

    class Event
    {
    public:
        Event() = default;
        virtual ~Event() = default;

        Event(const Event&) = default;
        Event(Event&&) = default;

        Event& operator=(const Event&) = default;
        Event& operator=(Event&&) = default;

        [[nodiscard]] virtual EventType Type() const = 0;
    };

}
