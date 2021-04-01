#pragma once

#include "Evil/Core/Base.h"

#ifdef EVIL_PLATFORM_WINDOWS

extern Evil::Application* Evil::CreateApplication();

int main(int argc, char** argv)
{
	Evil::Log::Init();


	EVIL_PROFILE_BEGIN_SESSION("Startup", "EvilProfile-Startup.json");
	auto app = Evil::CreateApplication();
	EVIL_PROFILE_END_SESSION();

	EVIL_PROFILE_BEGIN_SESSION("Runtime", "EvilProfile-Runtime.json");
	app->Run();
	EVIL_PROFILE_END_SESSION();

	EVIL_PROFILE_BEGIN_SESSION("Shutdown", "EvilProfile-Shutdown.json");
	delete app;
	EVIL_PROFILE_END_SESSION();
	return 0;
}

#endif //EVIL_PLATFORM_WINDOWS
