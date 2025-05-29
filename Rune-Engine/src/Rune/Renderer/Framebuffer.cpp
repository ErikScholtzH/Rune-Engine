#include "rune_pch.h"

#include "FrameBuffer.h"
#include "Rune/Renderer/Renderer.h"

#include "Rune/Renderer/Platform/OpenGL/Buffers/OpenGLFramebuffer.h"

namespace Rune {
	Ref<Framebuffer> Framebuffer::Create(const FramebufferSpecification& specification) {
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None:    RUNE_CORE_ASSERT(false, "RendererAPI::None is currently not supported"); return nullptr;
		case RendererAPI::API::OpenGL: 	return CreateRef<OpenGLFramebuffer>(specification); // makes ref of FrameBuffer
		}

		RUNE_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
}

