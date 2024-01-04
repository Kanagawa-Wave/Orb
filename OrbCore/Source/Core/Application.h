#pragma once

#include "Graphics/GraphicsContext.h"

struct GLFWwindow;

int main(int argc, char** argv);

namespace Orb
{
	struct ApplicationCreateDesc
	{
		std::string Title;
		int Width, Height;

		ApplicationCreateDesc& SetTitle(const std::string& title)
		{
			Title = title;
			return *this;
		}

		ApplicationCreateDesc& SetSize(int width, int height)
		{
			Width = width, Height = height;
			return *this;
		}
	};


	class Application
	{
	public:
		Application(const ApplicationCreateDesc& desc);
		virtual ~Application();

		static Application& Get() { return *s_Instance; }

	private:
		void Run();

	private:
		GLFWwindow* m_Window;
		static Application* s_Instance;
		friend int ::main(int argc, char** argv);
	};

	Application* CreateApplication();
}