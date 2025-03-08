#pragma once

#include "Rune/Renderer/RendererAPI.h"

namespace Rune {

	class OpenGLRendererAPI : public RendererAPI {
	public:
		virtual void SetClearColour(const glm::vec4& color) override;
		virtual void Clear() override;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) override;
	};
	
}