#pragma once

#include "TreeRoot/Renderer/Renderer.h"

/* Temporary */
/*#include "glm.hpp"
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

	enum class ShaderDataType : unsigned int
	{
		Float, Float2, Float3, Float4,
		Int, Int2, Int3, Int4,
		Bool,
		Mat3, Mat4
	};

	class Shader
	{
	public:
		virtual ~Shader() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		static Shader* Create(const std::string& vertexSource, const std::string& fragmentSource);
	};


}