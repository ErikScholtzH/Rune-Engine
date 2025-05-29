#pragma once
#include "Rune/Layer.h"

#include "Rune/Core/Events/KeyEvent.h"
#include "Rune/Core/Events/MouseEvent.h"
#include "Rune/Core/Events/ApplicationEvent.h"

namespace Rune {
	class RUNE_API ImGuiLayer : public Layer {
	public:
		ImGuiLayer();
		~ImGuiLayer();
		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;
		virtual void OnEvent(Event& e) override;

		void Begin();
		void End();

		void BlockEvents(bool block) { m_BlockEvents = block; }

	private:
		float m_Time = 0.0f;
		bool m_BlockEvents = true;
	};
}