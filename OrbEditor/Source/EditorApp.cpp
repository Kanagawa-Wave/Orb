#include "pch.h"

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
		WindowCreateInfo info;
		info.setTitle("Editor")
			.setSize(800, 600);
		Window::Create(info);

		Context::Init();
	}

	Application::~Application()
	{
		Window::Destroy();
	}

	void Application::Run()
	{
		while (!Window::Get().ShouldClose())
		{
			Window::Get().OnUpdate();
		}
	}

	Application* CreateApplication()
	{
		return new EditorApp();
	}
}
