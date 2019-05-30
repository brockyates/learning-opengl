#include "pch.h"
#include "Window.h"
#include <utility>

#include "config/WindowDefaults.h"

#include "events/EventDispatcher.h"

#include "logging/GLDebugMessageCallback.h"

namespace Graphics {

    Window::Window(EventHandler<Event> eventCallback)
        : properties_(WindowDefaults::Properties)
        , window_(CreateGLFWWindow(properties_))
        , input_(window_.get())
        , eventCallback_(std::move(eventCallback))
    {
#ifdef APP_DEBUG
        glEnable(GL_DEBUG_OUTPUT);
        glDebugMessageCallback(GLDebugMessageCallback, nullptr);
#endif
    }

    Window::~Window()
    {
        glfwTerminate();
    }

    EventHandler<AspectRatioChangeEvent> Window::OnAspectRatioChange()
    {
        return [this](const AspectRatioChangeEvent& event)
        {
            properties_.AspectRatio = event.NewAspectRatio();
        };
    }

    EventHandler<ResolutionChangeEvent> Window::OnResolutionChange()
    {
        return [this](const ResolutionChangeEvent& event)
        {
            properties_.Resolution = event.NewResolution();
        };
    }

    EventHandler<ChangeToWindowedEvent> Window::OnChangeToWindowed()
    {
        return [this](const ChangeToWindowedEvent&)
        {
            properties_.Mode = WindowMode::Windowed;
            glfwHideWindow(window_.get());
            glfwSetWindowMonitor(window_.get(), nullptr, 0, 0, properties_.Layout.Width, properties_.Layout.Height, GLFW_DONT_CARE);
            glfwSetWindowPos(window_.get(), properties_.Layout.Xpos, properties_.Layout.Ypos);
            glfwShowWindow(window_.get());

            FireEvent(AspectRatioChangeEvent(properties_.Layout.WindowedAspectRatio));
        };
    }

    EventHandler<ChangeToFullscreenEvent> Window::OnChangeToFullscreen()
    {
        return [this](const ChangeToFullscreenEvent&)
        {
            properties_.Mode = WindowMode::Fullscreen;
            glfwGetWindowSize(window_.get(), &properties_.Layout.Width, &properties_.Layout.Height);
            glfwGetWindowPos(window_.get(), &properties_.Layout.Xpos, &properties_.Layout.Ypos);
            glfwSetWindowMonitor(window_.get(), glfwGetPrimaryMonitor(), 0, 0, properties_.Resolution.Width, properties_.Resolution.Height, GLFW_DONT_CARE);
            glfwShowWindow(window_.get());
            glfwFocusWindow(window_.get());
            glfwSwapInterval(1);

            properties_.Layout.WindowedAspectRatio = properties_.AspectRatio;
            FireEvent(AspectRatioChangeEvent(static_cast<float>(properties_.Resolution.Width) / static_cast<float>(properties_.Resolution.Height)));
        };
    }

    EventHandler<WindowCloseEvent> Window::OnWindowClose()
    {
        return [this](const WindowCloseEvent&)
        {
            glfwSetWindowShouldClose(window_.get(), GLFW_TRUE);
        };
    }

    bool Window::ShouldClose() const
    {
        return glfwWindowShouldClose(window_.get());
    }

    bool Window::IsFullscreen() const
    {
        return properties_.Mode == WindowMode::Fullscreen;
    }

    void Window::Update() const
    {
        glfwSwapBuffers(window_.get());
        glfwPollEvents();
    }

    void Window::OnEvent(const Event& event)
    {
        EventDispatcher dispatcher(event);

        dispatcher.Dispatch<ResolutionChangeEvent>(OnResolutionChange());
        dispatcher.Dispatch<ChangeToWindowedEvent>(OnChangeToWindowed());
        dispatcher.Dispatch<ChangeToFullscreenEvent>(OnChangeToFullscreen());
        dispatcher.Dispatch<WindowCloseEvent>(OnWindowClose());
        dispatcher.Dispatch<AspectRatioChangeEvent>(OnAspectRatioChange());
    }

}
