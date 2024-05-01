#include "trpch.h"
#include "Shader.h"

#include "TreeRoot/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace tr {
	Ref<Shader> Shader::Create(const std::string& filePath)
	{
		switch (Renderer::GetCurrentAPI())
		{
			case RendererAPI::API::None:	TR_CORE_ASSERT(false, "RendererAPI::None") return nullptr;
			case RendererAPI::API::OpenGL:	return std::make_shared<OpenGLShader>(filePath);
		}
		TR_CORE_ASSERT(false, "Unknown renderer API!");

		return nullptr;
	}

	Ref<Shader> Shader::Create(const std::string& vertexSource, const std::string& fragmentSource)
    {
		switch (Renderer::GetCurrentAPI())
		{
			case RendererAPI::API::None:	TR_CORE_ASSERT(false, "RendererAPI::None") return nullptr;
			case RendererAPI::API::OpenGL:	return std::make_shared<OpenGLShader>(vertexSource, fragmentSource);
		}
		TR_CORE_ASSERT(false, "Unknown renderer API!");

		return nullptr;
    }

	// ShaderLibrary =============================

	void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader)
	{
		TR_CORE_ASSERT(!IsShaderExist(name), "Shader already exists!");
		m_Shaders.emplace(name, shader);
	}

	void ShaderLibrary::Add(const Ref<Shader>& shader)
	{
		auto& name = shader->GetName();
		Add(name, shader);
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& filePath)
	{
		auto shader = Shader::Create(filePath);
		Add(name, shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& filePath)
	{
		auto shader = Shader::Create(filePath);
		Add(shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Get(const std::string& name)
	{
		TR_CORE_ASSERT(IsShaderExist(name), "Shader not exist!");
		return m_Shaders[name];
	}

	bool ShaderLibrary::IsShaderExist(const std::string& name) const
	{
		return m_Shaders.find(name) != m_Shaders.end();
	}

}
