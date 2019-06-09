#include "pch.h"
#include "ShaderHelpers.h"

#include "logging/Log.h"

#include "renderer/RendererTypes.h"
#include "renderer/Renderer.h"

#include <glad/glad.h>

#include <fstream>
#include <sstream>

namespace Graphics {

    namespace {

        std::string Parse(const std::string& filePath)
        {
            const std::ifstream shaderFile(filePath);

            if (shaderFile.fail()) {
                LogError([&]()
                {
                    std::stringstream ss;
                    ss << "Can't open shader file: " << filePath << ". Does the file exist?";
                    return ss.str();
                }());
            }

            std::stringstream ss;
            ss << shaderFile.rdbuf();

            return ss.str();
        }

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
    }

    unsigned int CreateShader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
    {
        LogGlTrace([&]()
        {
            std::stringstream ss;
            ss << "Creating shader: {VertexShader:\"" << vertexShaderPath << R"(", FragmentShader:")" << fragmentShaderPath << "\"}";
            return ss.str();
        }());

        Renderer renderer;

        const auto program = renderer.CreateProgram();
        const auto vertexShader = Compile(GL_VERTEX_SHADER, Parse(vertexShaderPath));
        const auto fragmentShader = Compile(GL_FRAGMENT_SHADER, Parse(fragmentShaderPath));

        glAttachShader(program.AsGlType(), vertexShader);
        glAttachShader(program.AsGlType(), fragmentShader);
        glLinkProgram(program.AsGlType());
        glValidateProgram(program.AsGlType());

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        return program.AsGlType();
    }

}
