#pragma once

#include "Application.h"

extern Orb::Application* Orb::CreateApplication();

int main(int argc, char** argv)
{
	auto app = Orb::CreateApplication();
	app->Run();
	delete app;
}