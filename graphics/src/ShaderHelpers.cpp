#include "pch.h"
#include "ShaderHelpers.h"

#include "logging/Log.h"
#include "Window.h"

#include <glad/glad.h>

#include <fstream>
#include <sstream>

namespace Graphics {

    namespace {

        std::string Parse(const std::string& filePath)
        {
            std::ifstream shaderFile(filePath);

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

        unsigned int Compile(unsigned int type, const std::string& shaderSource)
        {
            const auto shaderId = glCreateShader(type);
            const auto source = shaderSource.c_str();
            glShaderSource(shaderId, 1, &source, nullptr);
            glCompileShader(shaderId);

            int shaderCompileStatus = GL_FALSE;
            glGetShaderiv(shaderId, GL_COMPILE_STATUS, &shaderCompileStatus);
            if (shaderCompileStatus == GL_FALSE)
            {
                int msgLength = 0;
                glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &msgLength);
                auto msg = (char*)alloca(msgLength * sizeof(char));
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

    unsigned int CreateShader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
    {
        LOG_GL_TRACE([&]()
        {
            std::stringstream ss;
            ss << "Creating shader: {VertexShader:\"" << vertexShaderPath << "\", \"FragmentShader:\"" << fragmentShaderPath << "}";
            return ss.str();
        }());

        const auto program = glCreateProgram();
        const auto vertexShader = Compile(GL_VERTEX_SHADER, Parse(vertexShaderPath));
        const auto fragmentShader = Compile(GL_FRAGMENT_SHADER, Parse(fragmentShaderPath));

        glAttachShader(program, vertexShader);
        glAttachShader(program, fragmentShader);
        glLinkProgram(program);
        glValidateProgram(program);

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        return program;
    }

}
