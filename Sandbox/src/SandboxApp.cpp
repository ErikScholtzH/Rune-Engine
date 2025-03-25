#include <Rune.h>

#include "glm/glm.hpp"
#include "imgui.h"
#include <filesystem>


class ExampleLayer : public Rune::Layer {
public:
	ExampleLayer() : Layer("Example"), m_SquarePosition(0.0f) {
		m_CameraController = Rune::CameraController(10.0f / 9.0f, Rune::Camera::CameraType::Perspective, glm::vec3(0.0f,0.0f,2.0f));

		m_VertexArray = Rune::VertexArray::Create();

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f
		};

		Rune::Ref<Rune::VertexBuffer> vertexBuffer;
		vertexBuffer = Rune::VertexBuffer::Create(vertices, sizeof(vertices));
		Rune::BufferLayout layout = {
			{ Rune::ShaderDataType::Float3, "a_Position" },
			{ Rune::ShaderDataType::Float4, "a_Color" }
		};

		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		Rune::Ref<Rune::IndexBuffer> indexBuffer;
		indexBuffer = Rune::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA = Rune::VertexArray::Create();
		float squareVertices[4 * 5] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};
		Rune::Ref<Rune::VertexBuffer> squareVB;
		squareVB = Rune::VertexBuffer::Create(squareVertices, sizeof(squareVertices));
		squareVB->SetLayout({
			{ Rune::ShaderDataType::Float3, "a_Position" },
			{ Rune::ShaderDataType::Float2, "a_TexCoord" }
			});
		m_SquareVA->AddVertexBuffer(squareVB);
		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Rune::Ref<Rune::IndexBuffer> squareIB;
		squareIB = Rune::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
		m_SquareVA->SetIndexBuffer(squareIB);

		// TODO find fix for hack
		static std::filesystem::path cwd = std::filesystem::path(__FILE__).parent_path().parent_path();
		static std::filesystem::path shader1 = cwd / "assets/shaders/m_shader.glsl";
		m_Shader = Rune::Shader::Create(shader1.string());

		static std::filesystem::path shader2 = cwd / "assets/shaders/blueSquare.glsl";
		m_BlueShader = Rune::Shader::Create(shader2.string());

		static std::filesystem::path shader3 = cwd / "assets/shaders/squareTexture.glsl";
		m_TextureShader = Rune::Shader::Create(shader3.string());
		
		static std::filesystem::path texture1 = cwd / "assets/textures/Wood01.png";
		m_Texture = Rune::Texture2D::Create(texture1.string());
		std::dynamic_pointer_cast<Rune::Shader>(m_TextureShader)->Bind();
		std::dynamic_pointer_cast<Rune::Shader>(m_TextureShader)->UploadUniformInt("u_Texture", 0);
	}

	void OnUpdate(Rune::Timestep timestep) override {
		RUNE_PROFILE_FUNCTION();
		glm::vec3 pos = m_CameraController.GetCamera().GetPosition();
		m_CameraController.OnUpdate(timestep);
		RUNE_PROFILE_SCOPE("CameraController::OnUpdate");
		RUNE_INFO("Camera Pos: ({0}, {1}, {2})", pos.x, pos.y, pos.z);

		RUNE_PROFILE_SCOPE("Renderer Prep");
		Rune::RenderCommand::SetClearColor({ 0.05f, 0.05f, 0.05f, 1 });
		Rune::RenderCommand::Clear();
		Rune::Renderer::BeginScene(m_CameraController.GetCamera());

		RUNE_PROFILE_SCOPE("Renderer Draw");
		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
		for (int y = 0; y < 20; y++) {
			for (int x = 0; x < 20; x++) {
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Rune::Renderer::Submit(m_SquareVA, m_BlueShader, transform);
			}
		}
		m_Texture->Bind();
		Rune::Renderer::Submit(m_SquareVA, m_TextureShader, glm::mat4(1.0f));
		Rune::Renderer::Submit(m_VertexArray, m_Shader);
		Rune::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override {
		RUNE_PROFILE_FUNCTION();
	}

	void OnEvent(Rune::Event& e) override {
		m_CameraController.OnEvent(e);
	}

private:
	Rune::Ref<Rune::Shader> m_Shader;
	Rune::Ref<Rune::VertexArray> m_VertexArray;
	Rune::Ref<Rune::Shader> m_BlueShader;
	
	Rune::Ref<Rune::VertexArray> m_SquareVA;

	Rune::CameraController m_CameraController;

	glm::vec3 m_SquarePosition;
	float m_SquareMoveSpeed = 1.0f;

	Rune::Ref<Rune::Shader> m_TextureShader;
	Rune::Ref<Rune::Texture2D> m_Texture;
};

class Sandbox : public Rune::Application {
public: 
	Sandbox() {
		PushLayer(new ExampleLayer());
	}

	~Sandbox() {

	}
};

Rune::Application* Rune::CreateApplication() {
	return new Sandbox();
}