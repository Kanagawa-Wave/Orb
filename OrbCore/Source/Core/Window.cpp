#include "pch.h"

#include "Window.h"

#include <GLFW/glfw3.h>

namespace Orb
{
	static uint8_t s_WindowCount = 0;

	Window* Window::Create(const WindowCreateInfo& info)
	{
		return new Window(info);
	}

	Window::~Window()
	{
		glfwDestroyWindow((GLFWwindow*)m_Window);
		s_WindowCount--;
		if (s_WindowCount == 0)
		{
			glfwTerminate();
		}
	}

	void Window::OnUpdate()
	{
		glfwPollEvents();
	}

	bool Window::ShouldClose() const
	{
		return glfwWindowShouldClose((GLFWwindow*)m_Window);
	}

	Window::Window(const WindowCreateInfo& info)
	{
		if (s_WindowCount == 0)
		{
			glfwInit();
		}

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		m_Window = (void*)glfwCreateWindow(info.Width, info.Height, info.Title.c_str(), nullptr, nullptr);
		s_WindowCount++;
	}
}


