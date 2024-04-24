#include "trpch.h"
#include "OpenGLTexture.h"

#include <glad/glad.h>

#include <stb/stb_image.h>

namespace tr {

	OpenGLTexture::OpenGLTexture(const std::string& path)
	{
		int width, height, channels;
		stbi_set_flip_vertically_on_load(1);
		stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		TR_CORE_ASSERT(data, "Failed to load image!");

		m_Width = width;
		m_Height = height;

		unsigned int storageFormat = 0, dataFormat = 0;
		if (channels == 3)
		{
			storageFormat = GL_RGB8;
			dataFormat = GL_RGB;
		}
		else if (channels == 4)
		{
			storageFormat = GL_RGBA8;
			dataFormat = GL_RGBA;
		}
		else
		{
			TR_CORE_ASSERT(false, "Unsupported Texture format!");
		}

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, storageFormat, m_Width, m_Height);

		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, data);
		stbi_image_free(data);
	}

	OpenGLTexture::~OpenGLTexture()
	{
		glDeleteTextures(1, &m_RendererID);
	}

	void OpenGLTexture::Bind(unsigned int slot) const
	{
		glBindTextureUnit(slot, m_RendererID);
	}

	void OpenGLTexture::Unbind() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}



}
