#include "rune_pch.h"

#include "Application.h"
#include "Rune/Core/Events/ApplicationEvent.h"
#include "Rune/Core/Log.h"

#include "Rune/Input.h"

#include "Rune/Renderer/Renderer.h"

#include "GLFW/glfw3.h"

namespace Rune {

#define BIND_EVENT_FN(fn) std::bind(&Application::fn, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	Application::Application() {
		RUNE_CORE_ASSERT(!s_Instance, "Application already running");
		s_Instance = this;

		m_Window = Scope<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		Renderer::Init();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}

	Application::~Application() {

	}

	void Application::PushLayer(Layer* layer) {
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* layer) {
		m_LayerStack.PushOverlay(layer);
	}

	void Application::OnEvent(Event& e) {
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(onWindowClose));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); ) {
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	void Application::run() { // GAME LOOP
		while (m_Running) {
			float time = glfwGetTime(); // TODO Temporary need to create platform specific code
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate(timestep);
			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();
			m_Window->OnUpdate();
		}
	}

	bool Application::onWindowClose(WindowCloseEvent& e) {
		this->m_Running = false;
		return true;
	}
}