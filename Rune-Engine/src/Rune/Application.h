#pragma once

#include "Core.h"
#include "Rune/Events/Event.h"
#include "Rune/Events/ApplicationEvent.h"
#include "Rune/LayerStack.h"

#include "Window.h"



namespace Rune {
	class RUNE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

	private:
		bool onWindowClose(WindowCloseEvent& e);
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
	};
	Application* CreateApplication(); //to be defined in a client
}


