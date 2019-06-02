#include "pch.h"
#include "ShaderHelpers.h"

#include "logging/Log.h"

#include <glad/glad.h>

#include <fstream>
#include <sstream>

namespace Graphics {

    namespace {

        std::string PARSE(const std::string& filePath)
        {
            const std::ifstream shaderFile(filePath);

            if (shaderFile.fail()) {
                LOG_ERROR([&]()
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

        unsigned int COMPILE(unsigned int type, const std::string& shaderSource)
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
                const auto msg = static_cast<char*>(alloca(msgLength * sizeof(char)));
                glGetShaderInfoLog(shaderId, msgLength, &msgLength, msg);

                LOG_GL_ERROR([&]()
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

    unsigned int CREATE_SHADER(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
    {
        LOG_GL_TRACE([&]()
        {
            std::stringstream ss;
            ss << "Creating shader: {VertexShader:\"" << vertexShaderPath << R"(", FragmentShader:")" << fragmentShaderPath << "\"}";
            return ss.str();
        }());

        const auto program = glCreateProgram();
        const auto vertexShader = COMPILE(GL_VERTEX_SHADER, PARSE(vertexShaderPath));
        const auto fragmentShader = COMPILE(GL_FRAGMENT_SHADER, PARSE(fragmentShaderPath));

        glAttachShader(program, vertexShader);
        glAttachShader(program, fragmentShader);
        glLinkProgram(program);
        glValidateProgram(program);

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        return program;
    }

}
