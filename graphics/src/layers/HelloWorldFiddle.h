#pragma once

#include "events/EventSystem.h"
#include "layers/Layer.h"
#include "ModelGenerator.h"
#include "models/Model.h"
#include "Timer.h"
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
        virtual void RenderUI() override;

        virtual void Attach() override;
        virtual void Detach() override;
        virtual bool IsAttached() const override { return m_Attached; }

        virtual std::string PopupText() const override;
        virtual std::string Description() const override;

        virtual void OnEvent(const Event& event) override;

    private:
        //This struct is only meaningful in the context of this demo, I don't want it to exist outside of HelloWorldFiddle.
        struct DrawMode
        {
            int Mode;
            unsigned int NumVertexes;
            std::string DisplayName;
        };

    private:
        //Event handlers
        EventHandler<RenderTargetChangedEvent> OnRenderTargetChanged();

        void UpdateVertexes();
        void UpdateVertex(glm::vec4& vertex, glm::vec4& direction);
        void UpdateTiming();
        void SetNextVertexPositions();
        void ChangeDrawMode(const DrawMode& nextMode);

    private:
        bool m_Attached = false;
        double m_LastTime = Timer::Get();
        double m_DeltaTime = 0;

        //OpenGL state
        unsigned int m_FrameBufferID = 0;
        unsigned int m_ShaderID = 0;
        unsigned int m_VertexArrayID = 0;
        unsigned int m_VertexBufferID = 0;
        unsigned int m_IndexBufferID = 0;
        unsigned int m_PointsizeUniformLocation = 0;

        glm::vec4 m_ClearColor = { 0.15f, 0.15f, 0.15f, 1.0f };
        float m_LineWidth = 5.0f;
        float m_PointSize = 30.0f;

        std::unordered_map<int, DrawMode> m_DrawModes{
            { GL_TRIANGLES, {GL_TRIANGLES, 3, "Triangles" }},
            { GL_LINES,     {GL_LINES,     6, "Lines"     }},
            { GL_POINTS,    {GL_POINTS,    3, "Points"    }}
        };

        DrawMode m_DrawMode = m_DrawModes[GL_TRIANGLES];

        //Buffer data
        std::unique_ptr<Model> m_TriangleModel = ModelGenerator::MakeTriangle();
        std::vector<unsigned int> m_LineIndexes = { 0, 1, 1, 2, 2, 0 };

        //Animation parameters
        bool m_AnimationEnabled = false;
        float m_VertexMoveSpeed = 0.5f;

        glm::vec4 m_Vertex1Direction = {  0.3f, -0.7f, 0.0f, 0.0f };
        glm::vec4 m_Vertex2Direction = {  0.1f, -0.5f, 0.0f, 0.0f };
        glm::vec4 m_Vertex3Direction = { -0.9f,  0.3f, 0.0f, 0.0f };
    };

}
