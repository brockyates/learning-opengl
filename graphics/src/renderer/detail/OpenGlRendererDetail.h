/*
 * OpenGlRendererDetail contains the NON-type-safe aspects of the OpenGL wrapper.
 */

#pragma once

#include "helpers/FileHelpers.h"
#include "helpers/GlobalMacros.h"

#include <glad/glad.h>

namespace Graphics::Detail
{
    template <typename TShader>
    constexpr auto GetGlShaderType()
    {
        if (std::is_same<TShader, VertexShader>::value)
        {
            return GL_VERTEX_SHADER;
        }

        if (std::is_same<TShader, FragmentShader>::value)
        {
            return GL_FRAGMENT_SHADER;
        }

        AppAssert(false, "Failed to compile shader: unknown shader type");
        return 0;
    }

    inline void ValidateShader(const GLuint id, const int type)
    {
        auto status = GL_FALSE;
        glGetShaderiv(id, GL_COMPILE_STATUS, &status);
        if (status == GL_FALSE)
        {
            auto msgLength = 0;
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &msgLength);
            const auto msg = std::make_unique<char[]>(msgLength);
            glGetShaderInfoLog(id, msgLength, &msgLength, msg.get());

            LogGlError([&]()
            {
                std::stringstream ss;
                ss << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader";
                return ss.str();
            }());

            glDeleteShader(id);
            AppAssert(false, "Failed to compile shader. Exiting.");
        }
    }

    template <typename TShader>
    TShader Compile(const std::string& shaderPath)
    {
        const auto type = GetGlShaderType<TShader>();
        const auto source = ParseFile(shaderPath);
        const auto shaderSource = source.c_str();

        const auto shaderId = glCreateShader(type);
        glShaderSource(shaderId, 1, &shaderSource, nullptr);
        glCompileShader(shaderId);

        ValidateShader(shaderId, type);

        return TShader{ shaderId };
    }
}
