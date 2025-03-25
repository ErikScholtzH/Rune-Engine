#include "rune_pch.h"

#include "LayerStack.h"

namespace Rune {

	LayerStack::LayerStack() {
		RUNE_PROFILE_FUNCTION();
		m_LayerInsert = m_Layers.begin();
	}

	LayerStack::~LayerStack() {
		RUNE_PROFILE_FUNCTION();
		for (Layer* layer : m_Layers)
			delete layer;
	}

	void LayerStack::PushLayer(Layer* layer){
		RUNE_PROFILE_FUNCTION();
		m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, layer);
		m_LayerInsertIndex++;
		layer->OnAttach();
	}

	void LayerStack::PushOverlay(Layer* overlay) {
		RUNE_PROFILE_FUNCTION();
		m_Layers.emplace_back(overlay);
		overlay->OnAttach();
	}

	void LayerStack::PopLayer(Layer* layer) {
		RUNE_PROFILE_FUNCTION();
		auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
		if (it != m_Layers.end()) {
			m_Layers.erase(it);
			m_LayerInsertIndex--;
			layer->OnDetach();
		}
	}

	void LayerStack::PopOverlay(Layer* overlay) {
		RUNE_PROFILE_FUNCTION();
		auto it = std::find(m_Layers.begin(), m_Layers.end(), overlay);
		if (it != m_Layers.end()) {
			m_Layers.erase(it);
			overlay->OnDetach();
		}
	}

}