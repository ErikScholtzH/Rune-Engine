#pragma once
#include "Rune/Core/Core.h"
#include "Debug/Instrumentator.h"

#ifdef RUNE_PLATFORM_WINDOWS

extern Rune::Application* Rune::CreateApplication();

int main(int argc, char** argv) {
	Rune::Log::Init();

	RUNE_CORE_INFO("Core logger set up");
	RUNE_INFO("Client logger set up");

	RUNE_PROFILE_BEGIN_SESSION("Init", "Profiling-Init.json");
	auto app = Rune::CreateApplication();
	RUNE_PROFILE_END_SESSION();

	RUNE_PROFILE_BEGIN_SESSION("Runtime", "Profiling-Runtime.json");
	app->run();
	RUNE_PROFILE_END_SESSION();

	RUNE_PROFILE_BEGIN_SESSION("Shutdown", "Profiling-Shutdown.json");
	delete app;
	RUNE_PROFILE_END_SESSION();

	return 0;
}
#else
	#error Rune Engine is only currently supported on windows
#endif