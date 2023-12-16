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
		m_Window = Window::Create(info);
	}

	Application::~Application()
	{
		delete m_Window;
	}

	void Application::Run()
	{
		while (!m_Window->ShouldClose())
		{
			m_Window->OnUpdate();
		}
	}

	Application* CreateApplication()
	{
		return new EditorApp();
	}
}
