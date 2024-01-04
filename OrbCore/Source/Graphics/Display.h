#pragma once

namespace Orb {

	struct DisplayCreateDesc
	{
		HWND Hwnd;
		uint32_t Width, Height, FrameCount;

		DisplayCreateDesc& SetHWND(HWND hwnd)
		{
			Hwnd = hwnd;
			return *this;
		}

		DisplayCreateDesc& SetSize(uint32_t width, uint32_t height)
		{
			Width = width, Height = height;
			return *this;
		}

		DisplayCreateDesc& SetFrameCount(uint32_t frameCount)
		{
			FrameCount = frameCount;
			return *this;
		}
	};

	class Display
	{
	public:
		static void Init(const DisplayCreateDesc& desc);
		static Display& Get() { return *s_Display; }

		~Display();
	private:
		Display(const DisplayCreateDesc& desc);

		static Display* s_Display;

		Microsoft::WRL::ComPtr<IDXGISwapChain4> m_SwapChain;
		Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> m_RTVHeap;
		std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> m_RenderTargets;
		uint32_t m_FrameIndex = 0;
		uint32_t m_RTVDescriptorSize = 0;
	};
}

