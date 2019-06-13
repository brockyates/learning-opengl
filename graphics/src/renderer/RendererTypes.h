#pragma once

#include "detail/IntId.h"
#include "detail/UintId.h"

namespace Graphics
{
    //32-bit unsigned integer IDs
    using FragmentShader = Detail::UintId<Detail::FragmentShaderTag>;
    using FrameBuffer = Detail::UintId<Detail::FrameBufferTag>;
    using IndexBuffer = Detail::UintId<Detail::IndexBufferTag>;
    using RenderBuffer = Detail::UintId<Detail::RenderBufferTag>;
    using ShaderProgram = Detail::UintId<Detail::ShaderProgramTag>;
    using Texture2d = Detail::UintId<Detail::Texture2dTag>;
    using VertexArray = Detail::UintId<Detail::VertexArrayTag>;
    using VertexBuffer = Detail::UintId<Detail::VertexBufferTag>;
    using VertexShader = Detail::UintId<Detail::VertexShaderTag>;

    //32-bit integer IDs
    using Uniform = Detail::IntId<Detail::UniformTag>;
}