#pragma once
#include "Event.h"

#include <string>
#include <sstream>

namespace Graphics {

    class WindowResizeEvent : public Event
    {
    public:
        WindowResizeEvent(unsigned int width, unsigned int height)
            : m_Width(width)
            , m_Height(height)
        {
        }

        inline unsigned int GetWidth() const { return m_Width; }
        inline unsigned int GetHeight() const { return m_Height; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "WindowResizeEvent: " << GetWidth() << ", " << GetHeight();
            return ss.str();
        }

        EVENT_CLASS_TYPE(WindowResize)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)

    private:
        unsigned int m_Width, m_Height;
    };

    class  WindowCloseEvent : public Event
    {
    public:
        WindowCloseEvent() {}

        EVENT_CLASS_TYPE(WindowClose)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };

    class  AppTickEvent : public Event
    {
        AppTickEvent() {}

        EVENT_CLASS_TYPE(AppTick)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };

    class  AppUpdateEvent : public Event
    {
        AppUpdateEvent() {}

        EVENT_CLASS_TYPE(AppUpdate)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };

    class  AppRenderEvent : public Event
    {
        AppRenderEvent() {}

        EVENT_CLASS_TYPE(AppRender)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };
}
