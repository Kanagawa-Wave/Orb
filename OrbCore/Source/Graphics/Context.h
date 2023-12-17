#pragma once

namespace Orb
{
	class Context
	{
	public:
		static Context* Create();

		~Context();

	private:
		Context();

		Microsoft::WRL::ComPtr<IDXGIFactory4> m_Factory;
		Microsoft::WRL::ComPtr<IDXGIAdapter1> m_Adapter;
		Microsoft::WRL::ComPtr<ID3D12Device> m_Device;
	};
}


