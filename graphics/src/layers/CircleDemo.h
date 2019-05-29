#pragma once

#include "events/Event.h"
#include "events/RenderTargetChangeEvent.h"
#include "events/AspectRatioChangeEvent.h"

#include "layers/Layer.h"

#include <glm/glm.hpp>

namespace Graphics {

    struct Circle;
    class Window;

    class CircleDemo : public Layer
    {
    public:
        CircleDemo(const Window& window, EventHandler<Event> eventCallback);

        virtual void RenderScene() override;
        virtual void RenderUI() override;
        virtual void OnEvent(const Event& event) override;
        virtual void Attach() override;
        virtual void Detach() override;
        virtual bool IsAttached() const override { return m_Attached; }
        virtual std::string PopupText() const override;
        virtual std::string Description() const override;

    private:
        //Event handlers
        EventHandler<RenderTargetChangeEvent> OnRenderTargetChange();
        EventHandler<AspectRatioChangeEvent> OnAspectRatioChange();

        //Scene rendering
        void UpdateTiming();
        void UpdateSides();
        void AnimateSides();

        constexpr static int m_MaxSides = 50;
        int m_Sides = m_MaxSides;
        int m_NextSides = m_MaxSides;
        unsigned int m_NumLineIndexes = 0;
        double m_TimeSinceLastChange = 0.0;
        float m_AnimationInterval = 0.5;
        bool m_SidesIncreasing = false;
        bool m_AnimationEnabled = false;

        std::unique_ptr<Circle> m_CircleModel = std::make_unique<Circle>(m_Sides);
        glm::mat4 m_ProjectionMatrix;

        //Layer state
        bool m_Attached = false;
        double m_LastTime;
        double m_DeltaTime = 0.0;

        //OpenGL state
        unsigned int m_FrameBufferID = 0;
        unsigned int m_TriangleShaderID = 0;
        unsigned int m_LineShaderID = 0;
        unsigned int m_VertexArrayID = 0;
        unsigned int m_VertexBufferID = 0;
        unsigned int m_TriangleIndexBufferID = 0;
        unsigned int m_LineIndexBufferID = 0;
        unsigned int m_TriangleProjMatrixUniformLocation = 0;
        unsigned int m_LineProjMatrixUniformLocation = 0;
        unsigned int m_LineColorUniformLocation = 0;
    };

}
