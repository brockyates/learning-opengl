#include "pch.h"
#include "HelloWorld.h"

#include "events/EventDispatcher.h"

#include "logging/Log.h"

#include "ShaderHelpers.h"
#include "Window.h"

#include <glad/glad.h>
#include <imgui.h>
#include <utility>

namespace Graphics {

    HelloWorld::HelloWorld(const Window& window, EventHandler<Event> eventCallback)
        : Layer(window, std::move(eventCallback), "Hello World")
    {}

    void HelloWorld::RenderScene()
    {
        if (!attached_)
            return;

        glBindFramebuffer(GL_FRAMEBUFFER, frameBufferId_);

        // Bindings
        glBindVertexArray(vertexArrayId_);
        glUseProgram(shaderId_);

        // Draw
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glViewport(0, 0, window_.ResolutionWidth(), window_.ResolutionHeight());
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Release bindings
        glUseProgram(0);
        glBindVertexArray(0);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void HelloWorld::RenderUi()
    {
        if (!attached_)
            return;

        ImGui::Begin("DemoWidget");

        ImGui::Dummy(ImVec2(0.0f, 20.0f));
        ImGui::TextWrapped("%s", Description().c_str());
        ImGui::Dummy(ImVec2(0.0f, 20.0f));
        ImGui::Separator();

        ImGui::End();
    }

    void HelloWorld::OnEvent(const Event& event)
    {
        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<RenderTargetChangeEvent>(OnRenderTargetChanged());
    }

    EventHandler<RenderTargetChangeEvent> HelloWorld::OnRenderTargetChanged()
    {
        return [this](const RenderTargetChangeEvent& event)
        {
            frameBufferId_ = event.NextRenderTargetId();
        };
    }

    void HelloWorld::Attach()
    {
        if (attached_) return;

        LOG_TRACE("Attaching HelloWorld");

        glGenVertexArrays(1, &vertexArrayId_);
        glBindVertexArray(vertexArrayId_);
        glGenBuffers(1, &vertexBufferId_);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId_);
        glBufferData(GL_ARRAY_BUFFER, std::size(vertexes_) * sizeof(float), &vertexes_[0], GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

        //Release bindings
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);

        shaderId_ = CREATE_SHADER("res/shaders/Minimal_Vertex.shader", "res/shaders/Minimal_Fragment.shader");

        attached_ = true;
    }

    void HelloWorld::Detach()
    {
        if (!attached_) return;

        LOG_TRACE("Detaching HelloWorld");

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);

        glDeleteProgram(shaderId_);
        glDeleteBuffers(1, &vertexBufferId_);

        attached_ = false;
    }

    std::string HelloWorld::PopupText() const
    {
        return "Draws triangle on minimal window";
    }

    std::string HelloWorld::Description() const
    {
        return "Hello World is a minimal demo. Draws a triangle on the window, and exposes no UI controls.";
    }

}
