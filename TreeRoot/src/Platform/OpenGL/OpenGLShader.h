#pragma once
#include "TreeRoot/Renderer/Shader.h"

namespace tr {

    class OpenGLShader : public Shader
    {
    public:
        OpenGLShader(const std::string& vertexSource, const std::string& fragmentSource);
        ~OpenGLShader();

        virtual void Bind() const override;
        virtual void Unbind() const override;
    private:
        unsigned int m_RendererID;
    };

}

