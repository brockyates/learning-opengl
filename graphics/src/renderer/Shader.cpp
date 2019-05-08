#include "pch.h"
#include "renderer/Shader.h"

#include "Renderer.h"

#include <glad/glad.h>

namespace Graphics {

    Shader::Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
        : m_RendererID(CreateShader(ParseShader(vertexShaderPath), ParseShader(fragmentShaderPath)))
    {
        LOG_DEBUG([&]() {
            std::stringstream ss;
            ss << "Shader(id=" << m_RendererID << ", vertexShaderPath=" << vertexShaderPath << ", fragmentShaderPath=" << fragmentShaderPath << ") created";
            return ss.str();
        }());
    }

    Shader::~Shader()
    {
        Unbind();
        GLCall(glDeleteProgram(m_RendererID));

        LOG_DEBUG([&]() {
            std::stringstream ss;
            ss << "Shader(id=" << m_RendererID << ") deleted";
            return ss.str();
        }());
    }

    void Shader::Bind() const
    {
        GLCall(glUseProgram(m_RendererID));
    }

    void Shader::Unbind() const
    {
        GLCall(glUseProgram(0));
    }

    void Shader::SetUniform1i(const std::string & name, int value)
    {
        GLCall(glUniform1i(GetUniformLocation(name), value));
    }

    void Shader::SetUniform1f(const std::string & name, float value)
    {
        GLCall(glUniform1f(GetUniformLocation(name), value));
    }

    void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
    {
        GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
    }

    void Shader::SetUniformMat4f(const std::string & name, const glm::mat4 & matrix)
    {
        GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
    }

    int Shader::GetUniformLocation(const std::string & name)
    {
        if (m_UniformLocationCache.find(name) != std::end(m_UniformLocationCache))
        {
            return m_UniformLocationCache[name];
        }

        GLCall(int uniformLocation = glGetUniformLocation(m_RendererID, name.c_str()));

        if (uniformLocation == -1)
        {
            LOG_WARN("Uniform '" + name + "' does not exist");
        }

        m_UniformLocationCache[name] = uniformLocation;

        return uniformLocation;
    }

    std::string Shader::ParseShader(const std::string& filePath)
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

    unsigned int Shader::CompileShader(unsigned int type, const std::string& shaderSource)
    {
        unsigned int shaderId = glCreateShader(type);
        const char* source = shaderSource.c_str();
        GLCall(glShaderSource(shaderId, 1, &source, nullptr));
        GLCall(glCompileShader(shaderId));

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

    unsigned int Shader::CreateShader(const std::string& vertexShaderSource,
                                      const std::string& fragmentShaderSource)
    {
        unsigned int program = glCreateProgram();
        unsigned int vertexShader = CompileShader(GL_VERTEX_SHADER, vertexShaderSource);
        unsigned int fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

        GLCall(glAttachShader(program, vertexShader));
        GLCall(glAttachShader(program, fragmentShader));
        GLCall(glLinkProgram(program));
        GLCall(glValidateProgram(program));

        GLCall(glDeleteShader(vertexShader));
        GLCall(glDeleteShader(fragmentShader));

        return program;
    }

}
