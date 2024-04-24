#pragma once

#include <glm/glm.hpp>

namespace tr {

	class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetShaderParameter(const std::string& name, int value) = 0;
		virtual void SetShaderParameter(const std::string& name, const glm::vec2& vector2) = 0;
		virtual void SetShaderParameter(const std::string& name, const glm::mat4& matrix4f) = 0;

		static Shader* Create(const std::string& vertexSource, const std::string& fragmentSource);
	};


}