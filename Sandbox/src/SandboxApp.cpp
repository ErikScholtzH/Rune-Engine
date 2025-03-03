#include <Rune.h>

class ExampleLayer : public Rune::Layer {
public:
	ExampleLayer() : Layer("Example") {}

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