#pragma once

#include "Rune/Core/Core.h"

#include "Rune/Core/Events/Event.h"
#include "Rune/Core/Events/ApplicationEvent.h"

#include "Window.h"
#include "Rune/LayerStack.h"
#include "ImGui/ImGuiLayer.h"

#include "Rune/Core/Timestep.h"

namespace Rune {
	class Application {
	public:
		Application();
		virtual ~Application();

		void run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline Window& GetWindow() { return *m_Window; }
		inline static Application& Get() { return *s_Instance; }
	private:
		bool onWindowClose(WindowCloseEvent& e);

		Scope<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;

		static Application* s_Instance;

	};
	Application* CreateApplication(); //to be defined in a client
}


