#pragma once

#include "Rune/Core/Core.h"

#include "Rune/Core/Events/Event.h"
#include "Rune/Core/Events/ApplicationEvent.h"
#include "Rune/Core/Timestep.h"

#include "Rune/LayerStack.h"
#include "ImGui/ImGuiLayer.h"

#include "Window.h"

namespace Rune {
	class Application {
	public:
		Application(const std::string name);
		virtual ~Application();

		void Run();
		void Close();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline Window& GetWindow() { return *m_Window; }
		inline static Application& Get() { return *s_Instance; }
		inline ImGuiLayer* GetImGuiLayer() { return m_ImGuiLayer; }

	private:
		bool onWindowClose(WindowCloseEvent& e);

		std::string m_Name;
		Scope<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;

		static Application* s_Instance;

	};
	Application* CreateApplication(); //to be defined in a client
}


