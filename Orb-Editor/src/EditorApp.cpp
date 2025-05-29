#include "Rune.h"

#include "Rune/EntryPoint.h"

#include "EditorLayer.h"

namespace Rune {

	class OrbEditor : public Application {
	public:
		OrbEditor() : Application("Orb Editor - Rune Engine") {
			PushLayer(new EditorLayer());
		}

		~OrbEditor() {

		}
	};

	Application* CreateApplication() {
		return new OrbEditor;
	}

}