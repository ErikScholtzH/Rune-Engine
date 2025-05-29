#include "rune_pch.h"

#include "OpenGLTexture2D.h"

#include <stb_image.h>

#include <filesystem>

namespace Rune {

	OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height) : m_Width(width), m_Height(height) {
		RUNE_PROFILE_FUNCTION();
		m_OpenGLFormat = GL_RGBA8;
		m_OpenGLDataFormat = GL_RGBA;

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, m_OpenGLFormat, m_Width, m_Height);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	OpenGLTexture2D::OpenGLTexture2D(const std::string& path) : m_Path(path) {
		RUNE_PROFILE_FUNCTION();
		int width;
		int height;
		int channels;

		stbi_set_flip_vertically_on_load(true);
		stbi_uc* data = nullptr;
		// RUNE_PROFILE_SCOPE("stbi_load - OpenGLTexture2D::OpenGLTexture2D(const std:string&)");  // TODO Fix
		data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		RUNE_CORE_ASSERT(data, "Failed to load image");

		m_Width = width;
		m_Height = height;

		m_OpenGLFormat = GL_RGBA8;
		m_OpenGLDataFormat = GL_RGBA;
		if (channels == 4) {
			m_OpenGLFormat = GL_RGBA8;
			m_OpenGLDataFormat = GL_RGBA;
		}
		else if (channels == 3) {
			m_OpenGLFormat = GL_RGB8;
			m_OpenGLDataFormat = GL_RGB;
		} 
		RUNE_CORE_ASSERT(m_OpenGLFormat & m_OpenGLDataFormat, "Failed to load image");

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, m_OpenGLFormat, m_Width, m_Height);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_OpenGLDataFormat, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);
	}

	OpenGLTexture2D::~OpenGLTexture2D() {
		RUNE_PROFILE_FUNCTION();
		glDeleteTextures(1, &m_RendererID);
	}

	void OpenGLTexture2D::Bind(uint32_t slot) const	{
		RUNE_PROFILE_FUNCTION();
		glBindTextureUnit(slot, m_RendererID);
	}

	void OpenGLTexture2D::Unbind(uint32_t slot) const {
		RUNE_PROFILE_FUNCTION();
		glBindTextureUnit(slot, 0);
	}

	void OpenGLTexture2D::SetData(void* data, uint32_t size) {
		RUNE_PROFILE_FUNCTION();
		uint32_t bpp;
		if (m_OpenGLDataFormat == GL_RGBA) {
			bpp = 4;
		}
		else {
			bpp = 3;
		}
		RUNE_CORE_ASSERT(size == m_Width * m_Height * bpp, "Data must be entire texture!");
		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_OpenGLDataFormat, GL_UNSIGNED_BYTE, data);
	}

}

