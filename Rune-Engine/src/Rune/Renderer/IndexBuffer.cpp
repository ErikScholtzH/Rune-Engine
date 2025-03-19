#include "rune_pch.h"

#include "IndexBuffer.h"

#include "Rune/Renderer/Renderer.h"
#include "Rune/Renderer/Platform/OpenGL/Buffers/OpenGLIndexBuffer.h"

namespace Rune {

	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t size){
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None:    RUNE_CORE_ASSERT(false, "RendererAPI::None is currently not supported"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateRef<OpenGLIndexBuffer>(indices, size);
		}

		RUNE_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

}