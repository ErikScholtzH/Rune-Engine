#pragma once

#include "Rune/Renderer/VertexArray.h"

#include <glm/glm.hpp>

namespace Rune {

	class RendererAPI {
	public:
		enum class API {
			None = 0, OpenGL = 1
		};

		virtual void Init() = 0;

		virtual void Clear() = 0;
		virtual void SetClearColour(const glm::vec4& colour) = 0;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) = 0;

		inline static API GetAPI(){ return s_API; }

	private:
		static API s_API;

	};
	
}
