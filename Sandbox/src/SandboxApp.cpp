#include <Rune.h>

#include "glm/glm.hpp"
#include "imgui.h"

class ExampleLayer : public Rune::Layer {
public:
	ExampleLayer() : Layer("Example"), m_SquarePosition(0.0f){
		m_Camera = Rune::Camera();

		m_VertexArray.reset(Rune::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f
		};

		Rune::Ref<Rune::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Rune::VertexBuffer::Create(vertices, sizeof(vertices)));
		Rune::BufferLayout layout = {
			{ Rune::ShaderDataType::Float3, "a_Position" },
			{ Rune::ShaderDataType::Float4, "a_Color" }
		};

		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		Rune::Ref<Rune::IndexBuffer> indexBuffer;
		indexBuffer.reset(Rune::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(Rune::VertexArray::Create());
		float squareVertices[3 * 4] = {
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f
		};
		Rune::Ref<Rune::VertexBuffer> squareVB;
		squareVB.reset(Rune::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ Rune::ShaderDataType::Float3, "a_Position" }
			});
		m_SquareVA->AddVertexBuffer(squareVB);
		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Rune::Ref<Rune::IndexBuffer> squareIB;
		squareIB.reset(Rune::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_TransformMatrix;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_TransformMatrix * vec4(a_Position, 1.0);	
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";
		m_Shader.reset(Rune::Shader::Create(vertexSrc, fragmentSrc));

		std::string blueShaderVertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_TransformMatrix;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;

				gl_Position = u_ViewProjection * u_TransformMatrix * vec4(a_Position, 1.0);	
			}
		)";

		std::string blueShaderFragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			void main()
			{
				color = vec4(0.2, 0.3, 0.8, 1.0);
			}
		)";
		m_BlueShader.reset(Rune::Shader::Create(blueShaderVertexSrc, blueShaderFragmentSrc));
	}

	void OnUpdate(Rune::Timestep timestep) override {

		if (Rune::Input::IsKeyPressed(RUNE_KEY_A)) {
			m_CameraPosition.x -= m_Camera.GetCameraSpeed() * timestep;
		}
		else if (Rune::Input::IsKeyPressed(RUNE_KEY_D)) {
			m_CameraPosition.x += m_Camera.GetCameraSpeed() * timestep;
		}
		else if (Rune::Input::IsKeyPressed(RUNE_KEY_SPACE)) {
			m_CameraPosition.y += m_Camera.GetCameraSpeed() * timestep;
		}
		else if (Rune::Input::IsKeyPressed(RUNE_KEY_LEFT_CONTROL)) {
			m_CameraPosition.y -= m_Camera.GetCameraSpeed() * timestep;
		}
		else if (Rune::Input::IsKeyPressed(RUNE_KEY_W)) {
			m_CameraPosition.z -= m_Camera.GetCameraSpeed() * timestep;
		}
		else if (Rune::Input::IsKeyPressed(RUNE_KEY_S)) {
			m_CameraPosition.z += m_Camera.GetCameraSpeed() * timestep;
		}
		else if (Rune::Input::IsKeyPressed(RUNE_KEY_UP)) {
			m_CameraRotation.x -= m_Camera.GetCameraRotationSpeed() * timestep;
		}
		else if (Rune::Input::IsKeyPressed(RUNE_KEY_DOWN)) {
			m_CameraRotation.x += m_Camera.GetCameraRotationSpeed() * timestep;
		}
		else if (Rune::Input::IsKeyPressed(RUNE_KEY_LEFT)) {
			m_CameraRotation.y += m_Camera.GetCameraRotationSpeed() * timestep;
		}
		else if (Rune::Input::IsKeyPressed(RUNE_KEY_RIGHT)) {
			m_CameraRotation.y -= m_Camera.GetCameraRotationSpeed() * timestep;
		}
		else if (Rune::Input::IsKeyPressed(RUNE_KEY_RIGHT)) {
			m_CameraRotation.y -= m_Camera.GetCameraRotationSpeed() * timestep;
		}

		m_Camera.SetRotation(m_CameraRotation);
		m_Camera.SetPosition(m_CameraPosition);
		Rune::RenderCommand::SetClearColor({ 0.05f, 0.05f, 0.05f, 1 });
		Rune::RenderCommand::Clear();
		Rune::Renderer::BeginScene(m_Camera);
		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
		for (int y = 0; y < 20; y++) {
			for (int x = 0; x < 20; x++) {
				glm::vec3 pos(x * 0.20f, y * 0.20f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Rune::Renderer::Submit(m_SquareVA, m_BlueShader, transform);
			}
		}
		Rune::Renderer::Submit(m_VertexArray, m_Shader);
		Rune::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override {

	}

	void OnEvent(Rune::Event& e) override {

	}

private:
	Rune::Ref<Rune::Shader> m_Shader;
	Rune::Ref<Rune::VertexArray> m_VertexArray;
	Rune::Ref<Rune::Shader> m_BlueShader;
	Rune::Ref<Rune::VertexArray> m_SquareVA;

	Rune::Camera m_Camera;
	glm::vec3 m_CameraPosition = m_Camera.GetPosition();
	glm::vec3 m_CameraRotation = m_Camera.GetRotation();

	glm::vec3 m_SquarePosition;
	float m_SquareMoveSpeed = 1.0f;
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