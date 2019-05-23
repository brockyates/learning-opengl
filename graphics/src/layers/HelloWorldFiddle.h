#pragma once

#include "events/EventSystem.h"
#include "layers/Layer.h"
#include "types/Vertex1.h"
#include "Window.h"

#include <glm/glm.hpp>

namespace Graphics {

    struct WindowProperties;

    struct DrawMode
    {
        int Mode;
        unsigned int NumVertexes;
        std::string DisplayName;
    };

    class HelloWorldFiddle : public Layer
    {
    public:
        HelloWorldFiddle(const Window& window, EventHandler<Event> eventCallback);

        virtual void RenderScene() override;
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

        void UpdateVertexes();
        void ChangeDrawMode(const DrawMode& nextMode);

    private:
        //OpenGL state
        unsigned int m_FrameBufferID = 0;
        unsigned int m_ShaderID = 0;
        unsigned int m_VertexArrayID = 0;
        unsigned int m_VertexBufferID = 0;
        unsigned int m_IndexBufferID = 0;

        glm::vec4 m_ClearColor = { 0.15f, 0.15f, 0.15f, 1.0f };

        glm::vec4 m_Vertex1Color = { 1.0f, 0.0f, 0.0f, 1.0f };
        glm::vec4 m_Vertex2Color = { 0.0f, 1.0f, 0.0f, 1.0f };
        glm::vec4 m_Vertex3Color = { 0.0f, 0.0f, 1.0f, 1.0f };

        glm::vec2 m_Vertex1Pos = { 0.0f,  1.0f };
        glm::vec2 m_Vertex2Pos = { 1.0f, -1.0f };
        glm::vec2 m_Vertex3Pos = {-1.0f, -1.0f };

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

        std::vector<unsigned int> m_TriangleIndexes = { 0, 1, 2 };
        std::vector<unsigned int> m_LineIndexes = { 0, 1, 1, 2, 2, 0 };

    private:
        bool m_Attached = false;

        std::unordered_map<int, DrawMode> m_DrawModes{
            { GL_TRIANGLES, {GL_TRIANGLES, 3, "Triangles" }},
            { GL_LINES,     {GL_LINES,     6, "Lines"     }},
            { GL_POINTS,    {GL_POINTS,    3, "Points"    }}
        };

        DrawMode m_DrawMode = m_DrawModes[GL_TRIANGLES];

        float m_LineWidth = 5.0f;
    };

}
