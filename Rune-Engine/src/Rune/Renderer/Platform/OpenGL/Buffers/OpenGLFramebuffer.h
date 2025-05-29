#pragma once

#include "Rune/Renderer/Framebuffer.h"


namespace Rune {

	class OpenGLFramebuffer : public Framebuffer {
	public:
		OpenGLFramebuffer(const FramebufferSpecification specification);
		virtual ~OpenGLFramebuffer();

		virtual void Invalidate();

		virtual void Bind() override;
		virtual void Unbind() override;
		virtual void Resize(uint32_t width, uint32_t height) override;

		virtual const FramebufferSpecification& GetFramebufferSpecification() const override { return m_Specification; }
		virtual uint32_t GetColourAttachmentRendererID() override { return m_ColourAttachment; }
	private:
		FramebufferSpecification m_Specification;
		uint32_t m_RendererID = 0;
		uint32_t m_ColourAttachment = 0;
		uint32_t m_DepthAttachment = 0;
	};
}