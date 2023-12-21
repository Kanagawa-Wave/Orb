#include "pch.h"

#include "Window.h"

#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

namespace Orb
{
	Window* Window::s_Window = nullptr;

	void Window::Create(const WindowCreateInfo& info)
	{
		s_Window = new Window(info);
	}

	void Window::Destroy()
	{
		delete s_Window;
	}

	Window::~Window()
	{
		glfwDestroyWindow((GLFWwindow*)m_Window);
		glfwTerminate();
	}

	void Window::OnUpdate()
	{
		glfwPollEvents();
	}

	bool Window::ShouldClose() const
	{
		return glfwWindowShouldClose((GLFWwindow*)m_Window);
	}

	std::pair<int, int> Window::GetSize()
	{
		std::pair<int, int> size;
		glfwGetWindowSize((GLFWwindow*)m_Window, &size.first, &size.second);
		return size;
	}

	HWND Window::GetHWND()
	{
		return glfwGetWin32Window((GLFWwindow*)m_Window);
	}

	Window::Window(const WindowCreateInfo& info)
	{
			glfwInit();

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		m_Window = (void*)glfwCreateWindow(info.Width, info.Height, info.Title.c_str(), nullptr, nullptr);
	}
}


