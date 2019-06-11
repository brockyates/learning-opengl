#pragma once

#include "detail/Int32Id.h"
#include "detail/Uint32Id.h"

namespace Graphics {

    //32-bit unsigned integer IDs
    using FragmentShader = Detail::Uint32Id<Detail::FragmentShaderTag>;
    using FrameBuffer = Detail::Uint32Id<Detail::FrameBufferTag>;
    using IndexBuffer = Detail::Uint32Id<Detail::IndexBufferTag>;
    using RenderBuffer = Detail::Uint32Id<Detail::RenderBufferTag>;
    using ShaderProgram = Detail::Uint32Id<Detail::ShaderProgramTag>;
    using Texture2d = Detail::Uint32Id<Detail::Texture2dTag>;
    using VertexArray = Detail::Uint32Id<Detail::VertexArrayTag>;
    using VertexBuffer = Detail::Uint32Id<Detail::VertexBufferTag>;
    using VertexShader = Detail::Uint32Id<Detail::VertexShaderTag>;

    //32-bit integer IDs
    using Uniform = Detail::Int32Id<Detail::UniformTag>;

}