#pragma once

namespace Orb
{
	class GraphicsContext
	{
	public:
		static void Init(void* window);
		static GraphicsContext& Get() { return *s_Context; }

		~GraphicsContext();

	private:
		static GraphicsContext* s_Context;

		GraphicsContext();

		friend class Display;

		Microsoft::WRL::ComPtr<IDXGIFactory4> m_Factory;
		Microsoft::WRL::ComPtr<IDXGIAdapter1> m_Adapter;
		Microsoft::WRL::ComPtr<ID3D12Device> m_Device;
		Microsoft::WRL::ComPtr<ID3D12CommandQueue> m_CommandQueue;
		Microsoft::WRL::ComPtr<ID3D12CommandAllocator> m_CommandAllocator;
	};
}


