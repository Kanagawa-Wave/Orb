#include "pch.h"
#include "Context.h"

#include "../../Display.h"

namespace Orb
{
	Context* Context::s_Context = nullptr;

	void Context::Init()
	{
		s_Context = new Context();
		Display::Init(2);
	}

	Context::~Context()
	{
		m_Factory->Release();
	}

	Context::Context()
	{
		// Create Factory
		UINT dxgiFactoryFlags = 0;

#if defined(_DEBUG)
		// Enable the debug layer (requires the Graphics Tools "optional feature").
		// NOTE: Enabling the debug layer after device creation will invalidate the active device.
		{
			Microsoft::WRL::ComPtr<ID3D12Debug> debugController;
			if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController))))
			{
				debugController->EnableDebugLayer();

				// Enable additional debug layers.
				dxgiFactoryFlags |= DXGI_CREATE_FACTORY_DEBUG;
			}
		}
#endif

		D3D_ASSERT(CreateDXGIFactory2(dxgiFactoryFlags, IID_PPV_ARGS(m_Factory.GetAddressOf())), "Failed to create DXGIFactory!")

		// Enumerate Adapter
		for (uint32_t i = 0; m_Factory->EnumAdapters1(i, m_Adapter.GetAddressOf()) != DXGI_ERROR_NOT_FOUND; i++)
		{
			DXGI_ADAPTER_DESC1 desc;
			m_Adapter->GetDesc1(&desc);

			if (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE)
				continue;

			if (D3D12CreateDevice(m_Adapter.Get(), D3D_FEATURE_LEVEL_12_0, _uuidof(ID3D12Device), nullptr) == S_OK)
				break;

			m_Adapter->Release();
		}

		// Create Device
		D3D_ASSERT(D3D12CreateDevice(m_Adapter.Get(), D3D_FEATURE_LEVEL_12_0, IID_PPV_ARGS(m_Device.GetAddressOf())), "Failed to create D3D12Device!")

		// Create Command Queue
		D3D12_COMMAND_QUEUE_DESC queueDesc{};
		queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
		queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;

		D3D_ASSERT(m_Device->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(m_CommandQueue.GetAddressOf())), "Failed to create D3D12CommandQueue!")
		D3D_ASSERT(m_Device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(m_CommandAllocator.GetAddressOf())), "Failed to create D3D12CommandAllocator!")
	}
}
