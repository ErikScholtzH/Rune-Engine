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

		void Begin();
		void End();

	private:
		float m_Time = 0.0f;
	};
}