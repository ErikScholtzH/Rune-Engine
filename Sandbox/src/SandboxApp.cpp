#include <Rune.h>

class ExampleLayer : public Rune::Layer {
public:
	ExampleLayer() : Layer("Example") {}

	void OnUpdate() override {
		RUNE_INFO("ExampleLayer::Update");
	}

	void OnEvent(Rune::Event& e) override {
		RUNE_INFO(e.ToString());
	}
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