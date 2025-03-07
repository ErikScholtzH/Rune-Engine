#include "rune_pch.h"

#include "VertexBuffer.h"

#include "Renderer.h"

#include "Rune/Renderer/Platform/OpenGL/Buffers/OpenGLVertexBuffer.h"

namespace Rune {

	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size) {
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None:    RUNE_CORE_ASSERT(false, "RendererAPI::None is currently not supported"); return nullptr;
		case RendererAPI::API::OpenGL:  return new OpenGLVertexBuffer(vertices, size);
		}

		RUNE_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

}