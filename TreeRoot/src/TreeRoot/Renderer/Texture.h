#pragma once

namespace tr {

	class Texture
	{
	public:
		virtual ~Texture() = default;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;
		
		virtual void Bind(unsigned int slot = 0) const = 0;
		virtual void Unbind() const = 0;

		static Ref<Texture> Create(const std::string& path);
	};

}