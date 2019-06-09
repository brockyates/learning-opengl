#include "pch.h"
#include "OpenGlRenderer.h"

#include "helpers/FileHelpers.h"

#include "logging/Log.h"

#include <glad/glad.h>

namespace Graphics
{
    namespace {

        unsigned int Compile(unsigned int type, const std::string& shaderSource)
        {
            const auto shaderId = glCreateShader(type);
            const auto source = shaderSource.c_str();
            glShaderSource(shaderId, 1, &source, nullptr);
            glCompileShader(shaderId);

            auto shaderCompileStatus = GL_FALSE;
            glGetShaderiv(shaderId, GL_COMPILE_STATUS, &shaderCompileStatus);
            if (shaderCompileStatus == GL_FALSE)
            {
                auto msgLength = 0;
                glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &msgLength);
                const auto msg = std::make_unique<char[]>(msgLength);
                glGetShaderInfoLog(shaderId, msgLength, &msgLength, msg.get());

                LogGlError([&]()
                {
                    std::stringstream ss;
                    ss << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader";
                    return ss.str();
                }());

                glDeleteShader(shaderId);
                return 0;
            }

            return shaderId;
        }

        VertexShader CompileVertexShader(const std::string& shaderPath)
        {
            return VertexShader{ Compile(GL_VERTEX_SHADER, ParseFile(shaderPath)) };
        }

        FragmentShader CompileFragmentShader(const std::string& shaderPath)
        {
            return FragmentShader{ Compile(GL_FRAGMENT_SHADER, ParseFile(shaderPath)) };
        }

        ShaderProgram CreateProgram()
        {
            return ShaderProgram{ glCreateProgram() };
        }

        void LinkProgram(const ShaderProgram& program)
        {
            glLinkProgram(program.AsGlType());
        }

        void ValidateProgram(const ShaderProgram& program)
        {
            glValidateProgram(program.AsGlType());
        }

        void AttachVertexShader(const ShaderProgram& program, const VertexShader& shader)
        {
            glAttachShader(program.AsGlType(), shader.AsGlType());
        }

        void AttachFragmentShader(const ShaderProgram& program, const FragmentShader& shader)
        {
            glAttachShader(program.AsGlType(), shader.AsGlType());
        }

        void DeleteVertexShader(const VertexShader& shader)
        {
            glDeleteShader(shader.AsGlType());
        }

        void DeleteFragmentShader(const FragmentShader& shader)
        {
            glDeleteShader(shader.AsGlType());
        }
    }

    ShaderProgram OpenGlRenderer::CreateShader(const std::string& vertexShaderPath,
        const std::string& fragmentShaderPath)
    {
        LogGlTrace([&]()
        {
            std::stringstream ss;
            ss << "Creating shader: {VertexShader:\"" << vertexShaderPath << R"(", FragmentShader:")" << fragmentShaderPath << "\"}";
            return ss.str();
        }());

        const auto program = CreateProgram();
        const auto vertexShader = CompileVertexShader(vertexShaderPath);
        const auto fragmentShader = CompileFragmentShader(fragmentShaderPath);

        AttachVertexShader(program, vertexShader);
        AttachFragmentShader(program, fragmentShader);
        LinkProgram(program);
        ValidateProgram(program);

        DeleteVertexShader(vertexShader);
        DeleteFragmentShader(fragmentShader);

        return program;
    }
}
