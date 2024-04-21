#pragma once
#include "TreeRoot/Renderer/Shader.h"

namespace tr {

    class OpenGLShader : public Shader
    {
    public:
        OpenGLShader(const std::string& vertexSource, const std::string& fragmentSource);
        virtual ~OpenGLShader();

        int GetUniformLocation(const std::string& name);
        virtual void SetUniform(const std::string& name, const glm::mat4& matrix4f) override;

        virtual void Bind() const override;
        virtual void Unbind() const override;
    private:
        unsigned int m_RendererID;
        std::unordered_map<std::string, unsigned int> m_UniformLocationsCache;
    };

}

