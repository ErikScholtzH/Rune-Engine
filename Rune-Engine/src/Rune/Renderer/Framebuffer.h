#pragma once

#include "Rune/Core/Core.h"

namespace Rune {
	struct FramebufferSpecification {
		uint32_t Width = 0;
		uint32_t Height = 0;
		uint32_t Samples = 1;
		// FrameBufferFormat Format = nullptr
		bool SwapChainTarget = false;
	};

	class Framebuffer {
	public:
		static Ref<Framebuffer> Create(const FramebufferSpecification& specification);

		virtual uint32_t GetColourAttachmentRendererID() = 0;

		virtual const FramebufferSpecification& GetFramebufferSpecification() const = 0;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		virtual void Resize(uint32_t width, uint32_t height) = 0;

	private:
		
	};
}