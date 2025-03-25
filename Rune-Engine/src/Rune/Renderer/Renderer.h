#pragma once

#include "Rune/Renderer/RenderCommand.h"
#include "Rune/Renderer/RendererAPI.h"

#include "Rune/Renderer/Camera.h"
#include "Rune/Renderer/Shader.h"

namespace Rune {

	class Renderer {
	public:

		static void Init();
		static void Shutdown();

		static void BeginScene(Camera& camera);
		static void EndScene();

		static void Submit(const Ref<VertexArray>& vertexArray, const Ref<Shader>& shader, const glm::mat4& transformMatrix = glm::mat4(1.0f));

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		struct SceneData {
			glm::mat4 ViewProjectionMatrix;
		};

		static Scope<SceneData> m_SceneData;
	};
}