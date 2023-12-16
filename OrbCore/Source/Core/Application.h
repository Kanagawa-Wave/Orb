#pragma once
#include "Window.h"

int main(int argc, char** argv);

namespace Orb
{
	class Application
	{
	public:
		Application();
		virtual ~Application();

		static Application& Get() { return *s_Instance; }

	private:
		void Run();

	private:
		Window* m_Window = nullptr;

		static Application* s_Instance;
		friend int ::main(int argc, char** argv);
	};

	Application* CreateApplication();
}