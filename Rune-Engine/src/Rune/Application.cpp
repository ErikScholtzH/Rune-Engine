#include "rune_pch.h"

#include "Application.h"
#include "Rune/Events/ApplicationEvent.h"
#include "Rune/Log.h"

#include <glad/glad.h>

#include "Rune/Input.h"

namespace Rune {

#define BIND_EVENT_FN(fn) std::bind(&Application::fn, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	Application::Application() {
		RUNE_CORE_ASSERT(!s_Instance, "Application already running");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
	}
	Application::~Application() {

	}

	void Application::PushLayer(Layer* layer) {
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer) {
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
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
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();
			auto [x, y] = Input::GetMousePos();
			//RUNE_TRACE("{0}, {1}", x, y);
			m_Window->OnUpdate();
		}
	}

	bool Application::onWindowClose(WindowCloseEvent& e) {
		this->m_Running = false;
		return true;
	}
}