#include <Rune.h>

#include "glm/glm.hpp"
#include "imgui.h"
#include <filesystem>

namespace Rune {
	class EditorLayer : public Layer {
	public:
		EditorLayer();

		void OnAttach();
		void OnDetach();
		void OnUpdate(Rune::Timestep timestep) override;
		virtual void OnImGuiRender() override;
		void OnEvent(Rune::Event& e) override;
	private:
		Ref<Shader> m_Shader;
		Ref<VertexArray> m_VertexArray;
		Ref<Shader> m_BlueShader;
		Ref<VertexArray> m_SquareVA;
		CameraController m_CameraController;
		glm::vec3 m_SquarePosition;
		float m_SquareMoveSpeed = 1.0f;
		Ref<Shader> m_TextureShader;
		Ref<Texture2D> m_Texture;
		Ref<Framebuffer> m_Framebuffer;
		glm::vec2 m_ViewportSize;
		bool m_IsViewportFocused = false;
		bool m_IsViewportHovered = false;
	};
}


