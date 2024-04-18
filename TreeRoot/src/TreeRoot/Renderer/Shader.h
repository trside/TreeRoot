#pragma once

namespace tr {

	class Shader
	{
	public:
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
	};

}