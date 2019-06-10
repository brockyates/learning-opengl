#pragma once

#include "detail/Uint32Id.h"

namespace Graphics {

    using FragmentShader = Detail::Uint32Id<Detail::FragmentShaderTag>;
    using FrameBuffer = Detail::Uint32Id<Detail::FrameBufferTag>;
    using IndexBuffer = Detail::Uint32Id<Detail::IndexBufferTag>;
    using ShaderProgram = Detail::Uint32Id<Detail::ShaderProgramTag>;
    using VertexArray = Detail::Uint32Id<Detail::VertexArrayTag>;
    using VertexBuffer = Detail::Uint32Id<Detail::VertexBufferTag>;
    using VertexShader = Detail::Uint32Id<Detail::VertexShaderTag>;

}