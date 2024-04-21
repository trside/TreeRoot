#pragma once

/* Temporary */
#include <glm/glm.hpp>

/*
typedef glm::fvec1 Float;
typedef glm::fvec2 Float2;
typedef glm::fvec3 Float3;
typedef glm::fvec4 Float4;
typedef glm::ivec1 Int;
typedef glm::ivec2 Int2;
typedef glm::ivec3 Int3;
typedef glm::ivec4 Int4;
typedef glm::bvec1 Bool;
typedef glm::mat3 Mat3;
typedef glm::mat4 Mat4;
*/
namespace tr {

	class Shader
	{
	public:
		virtual ~Shader() {}

		virtual void SetUniform(const std::string& name, const glm::mat4& matrix4f) = 0;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		static Shader* Create(const std::string& vertexSource, const std::string& fragmentSource);
	};


}