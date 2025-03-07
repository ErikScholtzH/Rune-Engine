#pragma once

#include "Rune/Renderer/RenderCommand.h"
#include "Rune/Renderer/RendererAPI.h"

#include "Rune/Renderer/Camera.h"
#include "Rune/Renderer/Shader.h"

namespace Rune {

	class Renderer {
	public:

		static void BeginScene(Camera& camera);
		static void EndScene();

		static void Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		struct SceneData {
			glm::mat4 ViewProjectionMatrix;
		};

		static SceneData* m_SceneData;
	};


}