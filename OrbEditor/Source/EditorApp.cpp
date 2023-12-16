#include <Core/EntryPoint.h>

namespace Orb
{
	class EditorApp : public Application
	{
	public:
		EditorApp() = default;
	};

	Application::Application()
	{
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
	}

	Application* CreateApplication()
	{
		return new EditorApp();
	}
}
