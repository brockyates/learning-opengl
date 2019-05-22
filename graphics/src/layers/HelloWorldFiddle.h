#pragma once

#include "events/EventSystem.h"
#include "layers/Layer.h"
#include "types/Vertex1.h"
#include "Window.h"

#include <glm/glm.hpp>

namespace Graphics {

    struct WindowProperties;

    class HelloWorldFiddle : public Layer
    {
    public:
        HelloWorldFiddle(const Window& window, EventHandler<Event> eventCallback);

        virtual void RenderScene() override;
        void UpdateVertexColors();

        virtual void RenderUI() override;

        virtual void Attach() override;
        virtual void Detach() override;
        virtual bool IsAttached() const override { return m_Attached; }

        virtual std::string PopupText() const override;
        virtual std::string Description() const override;

        virtual void OnEvent(const Event& event) override;

    private:
        //Event handlers
        EventHandler<RenderTargetChangedEvent> OnRenderTargetChanged();

    private:
        //OpenGL state
        unsigned int m_FrameBufferID = 0;
        unsigned int m_ShaderID = 0;
        unsigned int m_VertexArrayID = 0;
        unsigned int m_VertexBufferID = 0;

        glm::vec4 m_ClearColor = { 0.5f, 0.5f, 0.5f, 1.0f };
        glm::vec4 m_Vertex1Color = { 1.0f, 0.0f, 0.0f, 1.0f };
        glm::vec4 m_Vertex2Color = { 0.0f, 1.0f, 0.0f, 1.0f };
        glm::vec4 m_Vertex3Color = { 0.0f, 0.0f, 1.0f, 1.0f };

        std::vector<Vertex1> m_Vertexes =
        {
            {
                glm::vec4{ 0.0f,  1.0f, 0.0f, 1.0f }, //Position
                glm::vec4{ 1.0f,  0.0f, 0.0f, 1.0f }, //Color
            },
            {
                glm::vec4{ 1.0f, -1.0f, 0.0f, 1.0f },
                glm::vec4{ 0.0f,  1.0f, 0.0f, 1.0f },
            },
            {
                glm::vec4{-1.0f, -1.0f, 0.0f, 1.0f },
                glm::vec4{ 0.0f,  0.0f, 1.0f, 1.0f },
            }
        };

    private:
        bool m_Attached = false;
    };

}
