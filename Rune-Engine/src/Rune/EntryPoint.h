#pragma once

#ifdef RUNE_PLATFORM_WINDOWS

extern Rune::Application* Rune::CreateApplication();

int main(int argc, char** argv) {
	Rune::Log::Init();

	RUNE_CORE_WARN("Core logger set up");
	RUNE_INFO("Client logger set up");


	auto app = Rune::CreateApplication();
	app->run();
	delete app;

	return 0;
}
#else
	#error Rune is only currently supported on windows
#endif