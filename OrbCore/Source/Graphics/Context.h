#pragma once

namespace Orb
{
	class Context
	{
	public:
		static void Init();
		static Context& Get() { return *s_Context; }

		~Context();

	private:
		static Context* s_Context;

		Context();

		friend class Display;

		Microsoft::WRL::ComPtr<IDXGIFactory4> m_Factory;
		Microsoft::WRL::ComPtr<IDXGIAdapter1> m_Adapter;
		Microsoft::WRL::ComPtr<ID3D12Device> m_Device;
		Microsoft::WRL::ComPtr<ID3D12CommandQueue> m_CommandQueue;
		Microsoft::WRL::ComPtr<ID3D12CommandAllocator> m_CommandAllocator;
	};
}


