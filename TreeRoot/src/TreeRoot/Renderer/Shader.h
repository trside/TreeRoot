#pragma once

#include <glm/glm.hpp>

namespace tr {

	class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual const std::string& GetName() const = 0;

		virtual void SetShaderParameter(const std::string& name, int value) = 0;
		virtual void SetShaderParameter(const std::string& name, const glm::vec2& vector2) = 0;
		virtual void SetShaderParameter(const std::string& name, const glm::mat4& matrix4f) = 0;

		static Ref<Shader> Create(const std::string& filePath);
		static Ref<Shader> Create(const std::string& vertexSource, const std::string& fragmentSource);
	};

	class ShaderLibrary
	{
	public:
		void Add(const std::string& name, const Ref<Shader>& shader);
		void Add(const Ref<Shader>& shader);
		Ref<Shader> Load(const std::string& name, const std::string& filePath);
		Ref<Shader> Load(const std::string& filePath);

		Ref<Shader> Get(const std::string& name);
	private:
		bool IsShaderExist(const std::string& name) const;

		std::unordered_map<std::string, Ref<Shader>> m_Shaders;
	};
}