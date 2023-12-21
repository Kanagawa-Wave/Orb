#pragma once

namespace Orb {
	class Display
	{
	public:
		static void Init(uint32_t frameCount);
		static Display& Get() { return *s_Display; }

		~Display();
	private:
		Display(uint32_t frameCount);

		static Display* s_Display;

		Microsoft::WRL::ComPtr<IDXGISwapChain4> m_SwapChain;
		Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> m_RTVHeap;
		std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> m_RenderTargets;
		uint32_t m_FrameIndex = 0;
		uint32_t m_RTVDescriptorSize = 0;
	};
}

