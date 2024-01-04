#include "pch.h"

#include "Application.h"

#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

namespace Orb
{
	Application::Application(const ApplicationCreateDesc& desc)
	{
		glfwInit();

		m_Window = glfwCreateWindow(desc.Width, desc.Height, desc.Title.c_str(), nullptr, nullptr);
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

		GraphicsContext::Init(m_Window);
	}

	Application::~Application()
	{
		glfwDestroyWindow(m_Window);
		glfwTerminate();
	}

	void Application::Run()
	{
		while (!glfwWindowShouldClose(m_Window))
		{
			glfwPollEvents();
		}
	}

}
