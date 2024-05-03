#pragma once

#include "TreeRoot/Renderer/Shader.h"

namespace tr {

    class OpenGLShader : public Shader
    {
    public:
        OpenGLShader(const std::string& filePath);
        OpenGLShader(const std::string& vertexSource, const std::string& fragmentSource);
        virtual ~OpenGLShader();

        virtual void Bind() const override;
        virtual void Unbind() const override;

        virtual inline const std::string& GetName() const override { return m_Name; }

        virtual void SetShaderParameter(const std::string& name, int value) override;
        virtual void SetShaderParameter(const std::string& name, const glm::vec2& vector2) override;
        virtual void SetShaderParameter(const std::string& name, const glm::vec4& vector4) override;
        virtual void SetShaderParameter(const std::string& name, const glm::mat4& matrix4f) override;
    private:
        int GetUniformLocation(const std::string& name);

        std::string ReadFile(const std::string& filePath);
        std::unordered_map<unsigned int, std::string> Preprocess(const std::string& source);
        std::unordered_map<unsigned int, std::string> Preprocess(const std::string& vertexSource, const std::string& fragmentSource);
        unsigned int CompileShader(const std::unordered_map<unsigned int, std::string>& shaderSources);

        unsigned int GetShaderTypeFromString(const std::string& type);
    private:
        unsigned int m_RendererID;
        std::unordered_map<std::string, unsigned int> m_UniformLocationsCache;
        std::string m_Name;
    };

}

