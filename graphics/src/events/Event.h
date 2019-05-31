#pragma once

#include <functional>

namespace Graphics {

    enum class EventType;

    template <typename T>
    using EventHandler = std::function<void(const T&)>;

    class Event
    {
    public:
        virtual ~Event() = default;;

        [[nodiscard]] virtual EventType Type() const = 0;
    };

}
