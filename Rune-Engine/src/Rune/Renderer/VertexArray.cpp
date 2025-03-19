#include "rune_pch.h"
#include "VertexArray.h"

#include "Rune/Renderer/Renderer.h"

#include "Rune/Renderer/Platform/OpenGL/Buffers/OpenGLVertexArray.h"

namespace Rune {

	Ref<VertexArray> VertexArray::Create() {
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None:    RUNE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateRef<OpenGLVertexArray>();
		}

		RUNE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}