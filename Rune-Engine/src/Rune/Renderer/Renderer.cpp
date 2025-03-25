#include "rune_pch.h"
#include "Renderer.h"

namespace Rune {

	Scope<Renderer::SceneData> Renderer::m_SceneData = CreateScope<Renderer::SceneData>();

	void Renderer::Init(){
		RUNE_PROFILE_FUNCTION();
		RenderCommand::Init();
	}

	void Renderer::Shutdown() {
		RUNE_PROFILE_FUNCTION();
	}

	void Renderer::BeginScene(Camera& camera) {
		m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene() {
		RUNE_PROFILE_FUNCTION();
	}

	void Renderer::Submit(const Ref<VertexArray>& vertexArray, const Ref<Shader>& shader, const glm::mat4& transformMatrix) {
		RUNE_PROFILE_FUNCTION();
		shader->Bind();
		shader->UploadUniformMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
		shader->UploadUniformMat4("u_TransformMatrix", transformMatrix);
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
		
}