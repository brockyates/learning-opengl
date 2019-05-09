#include "pch.h"
#include "renderer/Shader.h"

#include "Window.h"

#include <glad/glad.h>

namespace Graphics {

    namespace {

        std::string Parse(const std::string& filePath)
        {
            std::ifstream file(filePath);
            if (file.fail()) {
                LOG_ERROR([&]()
                {
                    std::stringstream ss;
                    ss << "Can't open shader file: " << filePath << ". Does the file exist?";
                    return ss.str();
                }());
            }
            std::stringstream ss;
            ss << file.rdbuf();

            return ss.str();
        }

        unsigned int Compile(unsigned int type, const std::string& shaderSource)
        {
            unsigned int shaderId = glCreateShader(type);
            const char* source = shaderSource.c_str();
            glShaderSource(shaderId, 1, &source, nullptr);
            glCompileShader(shaderId);

            int result;
            glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result);
            if (result == GL_FALSE)
            {
                int length;
                glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &length);
                char* message = (char*)alloca(length * sizeof(char));
                glGetShaderInfoLog(shaderId, length, &length, message);

                LOG_ERROR([&]()
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
        LOG_TRACE([&]()
        {
            std::stringstream ss;
            ss << "Creating shader: {VertexShader:\"" << vertexShaderPath << "\", \"FragmentShader:\"" << fragmentShaderPath << "}";
            return ss.str();
        }());

        unsigned int program = glCreateProgram();
        unsigned int vertexShader = Compile(GL_VERTEX_SHADER, Parse(vertexShaderPath));
        unsigned int fragmentShader = Compile(GL_FRAGMENT_SHADER, Parse(fragmentShaderPath));

        glAttachShader(program, vertexShader);
        glAttachShader(program, fragmentShader);
        glLinkProgram(program);
        glValidateProgram(program);

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        return program;
    }

}
