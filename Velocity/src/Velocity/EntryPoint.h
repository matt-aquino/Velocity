#pragma once
#ifdef VL_PLATFORM_WINDOWS

extern Velocity::Application* Velocity::CreateApplication();

int main(int argc, char** argv)
{
	printf("Starting up...\n");
	Velocity::Log::Init();
	VL_CORE_WARN("Initialized Core!");
	VL_INFO("Initialized Client!");
	auto app = Velocity::CreateApplication();
	app->Run();
	delete app;
}

#else
	#error Velocity only supports Windows!

#endif