#pragma once

#include "TreeRoot/Renderer/Texture.h"

namespace tr {

	class OpenGLTexture : public Texture
	{
	public:
		OpenGLTexture(const std::string& path);
		virtual ~OpenGLTexture();

		virtual inline unsigned int GetWidth() const override { return m_Width; }
		virtual inline unsigned int GetHeight() const override { return m_Height; }

		virtual void Bind(unsigned int slot = 0) const override;
		virtual void Unbind() const override;
	private:
		unsigned int m_RendererID;
		unsigned int m_Width, m_Height;
	};

}