#pragma once

#include "Log.h"
#include "Application.h"

extern Orb::Application* Orb::CreateApplication();

int main(int argc, char** argv)
{
	Orb::Log::Init();

	auto app = Orb::CreateApplication();
	app->Run();
	delete app;
}