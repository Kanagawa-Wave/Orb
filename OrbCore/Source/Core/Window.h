#pragma once

namespace Orb
{
	struct WindowCreateInfo
	{
		std::string Title;
		int Width, Height;

		WindowCreateInfo& setTitle(const std::string& title)
		{
			Title = title;
			return *this;
		}

		WindowCreateInfo& setSize(int width, int height)
		{
			Width = width;
			Height = height;
			return *this;
		}
	};

	class Window
	{
	public:
		static void Create(const WindowCreateInfo& info);
		static void Destroy();

		static Window& Get() { return *s_Window; }

		void OnUpdate();

		bool ShouldClose() const;

		std::pair<int, int> GetSize();
		HWND GetHWND();

	private:
		Window(const WindowCreateInfo& info);
		~Window();

		static Window* s_Window;

		void* m_Window;
	};
}
