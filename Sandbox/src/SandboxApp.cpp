#include <Rune.h>

#include "glm/glm.hpp"

class ExampleLayer : public Rune::Layer {
public:
	ExampleLayer() : Layer("Example") {
		glm::vec2 baller = glm::vec2(0.6f, 0.5f);
		RUNE_INFO("{0}", baller.x);
	}

	void OnUpdate() override {
		//RUNE_INFO("ExampleLayer::Update");
		if (Rune::Input::IsKeyPressed(RUNE_KEY_TAB)) {
			RUNE_INFO("tab is pressed");
		}
	}

	void OnEvent(Rune::Event& e) override {
		//RUNE_INFO(e.ToString());
	}
};

class Sandbox : public Rune::Application {
public: 
	Sandbox() {
		PushLayer(new ExampleLayer());
		PushOverlay(new Rune::ImGuiLayer());
	}

	~Sandbox() {

	}
};

Rune::Application* Rune::CreateApplication() {
	return new Sandbox();
}