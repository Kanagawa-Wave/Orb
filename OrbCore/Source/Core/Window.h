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
		static Window* Create(const WindowCreateInfo& info);
		~Window();

		void OnUpdate();

		bool ShouldClose() const;

	private:
		Window(const WindowCreateInfo& info);

		void* m_Window;
	};
}
