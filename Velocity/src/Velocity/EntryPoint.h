#pragma once
#include <stdio.h>

#ifdef VL_PLATFORM_WINDOWS

extern Velocity::Application* Velocity::CreateApplication();

int main(int argc, char** argv)
{
	printf("Starting up...\n");
	auto app = Velocity::CreateApplication();
	app->Run();
	delete app;
}

#else
	#error Velocity only supports Windows!

#endif