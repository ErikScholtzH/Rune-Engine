#include "rune_pch.h"

#include "OpenGLRendererAPI.h"

#include <glad/glad.h>


namespace Rune {

	void OpenGLRendererAPI::Init() {
		RUNE_PROFILE_FUNCTION();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void OpenGLRendererAPI::SetClearColour(const glm::vec4& colour) {
		RUNE_PROFILE_FUNCTION();
		glClearColor(colour.r, colour.g, colour.b, colour.a);
	}

	void OpenGLRendererAPI::Clear() {
		RUNE_PROFILE_FUNCTION();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	} 

	void OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray>& vertexArray) {
		RUNE_PROFILE_FUNCTION();
		glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

}