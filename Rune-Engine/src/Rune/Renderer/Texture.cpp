#include "rune_pch.h"

#include "Texture.h"
#include "Rune/Renderer/Renderer.h"

#include "Rune/Renderer/Platform/OpenGL/Textures/OpenGLTexture2D.h"

namespace Rune {

	Ref<Texture2D> Texture2D::Create(const std::string& path) {
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None:    RUNE_CORE_ASSERT(false, "RendererAPI::None is currently not supported"); return nullptr;
		case RendererAPI::API::OpenGL: 	return std::make_shared<OpenGLTexture2D>(path); // makes ref of Texture2D
		}

		RUNE_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

}

