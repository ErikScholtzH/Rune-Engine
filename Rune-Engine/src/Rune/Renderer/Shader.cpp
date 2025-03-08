#include "rune_pch.h"

#include "Shader.h"

#include "Renderer.h"

#include "Rune/Renderer/Platform/OpenGL/Shaders/OpenGLShader.h"

namespace Rune {
	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc) {
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None:    RUNE_CORE_ASSERT(false, "RendererAPI::None is currently not supported"); return nullptr;
		case RendererAPI::API::OpenGL:  return new OpenGLShader(vertexSrc, fragmentSrc);
		}

		RUNE_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
}