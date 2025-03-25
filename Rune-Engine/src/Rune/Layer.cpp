#include "rune_pch.h"
#include "Layer.h"

namespace Rune {

	Layer::Layer(const std::string& debugName) : m_DebugName(debugName) {
		RUNE_PROFILE_FUNCTION();
	}

	Layer::~Layer() {
		RUNE_PROFILE_FUNCTION();
	}

}