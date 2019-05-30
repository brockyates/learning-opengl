#pragma once

#include "events/Event.h"
#include "events/AspectRatioChangeEvent.h"
#include "events/RenderTargetChangeEvent.h"

#include "layers/Layer.h"

#include <glm/glm.hpp>

namespace Graphics {

    struct WindowProperties;
    class Model;
    class Window;

    class HelloWorldFiddle : public Layer
    {
    public:
        HelloWorldFiddle(const Window& window, EventHandler<Event> eventCallback);

        virtual void RenderScene() override;
        virtual void RenderUI() override;

        virtual void Attach() override;
        virtual void Detach() override;
        [[nodiscard]] virtual bool IsAttached() const override { return m_Attached; }

        [[nodiscard]] virtual std::string PopupText() const override;
        [[nodiscard]] virtual std::string Description() const override;

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
        EventHandler<RenderTargetChangeEvent> OnRenderTargetChanged();
        EventHandler<AspectRatioChangeEvent> OnAspectRatioChange();

    private:
        //Scene rendering
        void UpdateVertexes();
        void UpdateVertex(glm::vec4& vertex, glm::vec4& direction);
        void UpdateTiming();
        void SetNextVertexPositions();
        void ChangeDrawMode(const DrawMode& nextMode);
        [[nodiscard]] glm::vec4 GetRandomVertexDirection() const;

    private:
        //UI Rendering
        void DrawDescription() const;
        void DrawModeSelector();
        void DrawColorControls();
        void DrawPositionControls();
        void DrawLineControls();
        void DrawPointControls();

    private:
        bool m_Attached = false;
        double m_LastTime;
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

        std::unordered_map<int, DrawMode> m_DrawModes;
        DrawMode m_DrawMode;

        //Buffer data
        std::unique_ptr<Model> m_TriangleModel;
        std::vector<unsigned int> m_LineIndexes = { 0, 1, 1, 2, 2, 0 };

        //Animation parameters
        bool m_AnimationEnabled = false;
        float m_VertexMoveSpeed = 0.5f;

        glm::vec4 m_Vertex1Direction = GetRandomVertexDirection();
        glm::vec4 m_Vertex2Direction = GetRandomVertexDirection();
        glm::vec4 m_Vertex3Direction = GetRandomVertexDirection();

        glm::mat4 m_ProjectionMatrix;
        unsigned int m_ProjMatrixUniformLocation = 0;
    };

}
