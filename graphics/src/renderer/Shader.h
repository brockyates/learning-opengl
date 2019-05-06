#pragma once

#include <glm/glm.hpp>

namespace Graphics {

    class Shader
    {
    public:
        Shader(const std::string& vertexShader, const std::string& fragmentShader);
        ~Shader();

        Shader(Shader&) = delete;
        Shader& operator=(Shader&) = delete;

        Shader(Shader&&) = default;
        Shader& operator=(Shader&&) = default;

        void Bind() const;
        void Unbind() const;

        void SetUniform1i(const std::string& name, int value);
        void SetUniform1f(const std::string& name, float value);
        void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
        void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);

    private:
        int GetUniformLocation(const std::string& name);

        std::string ParseShader(const std::string& filePath);
        unsigned int CompileShader(unsigned int type, const std::string& shaderSource);
        unsigned int CreateShader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);

    private:
        unsigned int m_RendererID;
        std::unordered_map<std::string, int> m_UniformLocationCache;
    };

}
