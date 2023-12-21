#include "pch.h"
#include "Display.h"

#include "Core/Window.h"
#include "Graphics/Context.h"

namespace Orb
{
	Display* Display::s_Display = nullptr;

	void Display::Init(uint32_t frameCount)
	{
		s_Display = new Display(frameCount);
	}

	Display::~Display()
	{
	}

	Display::Display(uint32_t frameCount)
	{
		Microsoft::WRL::ComPtr<IDXGIFactory4> factory;
		D3D_ASSERT(CreateDXGIFactory2(0, IID_PPV_ARGS(factory.GetAddressOf())), "Failed to create DXGIFactory!")

		DXGI_SWAP_CHAIN_DESC1 swapChainDesc{};
		const auto size = Window::Get().GetSize();
		swapChainDesc.Width = size.first;
		swapChainDesc.Height = size.second;
		swapChainDesc.Format = DXGI_FORMAT_R10G10B10A2_UNORM;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	    swapChainDesc.BufferCount = frameCount;
	    swapChainDesc.SampleDesc.Count = 1;
	    swapChainDesc.SampleDesc.Quality = 0;
	    swapChainDesc.Scaling = DXGI_SCALING_NONE;
	    swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	    swapChainDesc.AlphaMode = DXGI_ALPHA_MODE_IGNORE;
	    swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

		DXGI_SWAP_CHAIN_FULLSCREEN_DESC fsSwapChainDesc = {};
		fsSwapChainDesc.Windowed = TRUE;

		Microsoft::WRL::ComPtr<IDXGISwapChain1> swapChain;
		D3D_ASSERT(factory->CreateSwapChainForHwnd(Context::Get().m_CommandQueue.Get(), Window::Get().GetHWND(), &swapChainDesc, &fsSwapChainDesc, nullptr, swapChain.GetAddressOf()), "Failed to create DXGISwapchain!")

		m_SwapChain = (IDXGISwapChain4*)swapChain.Get();

		m_FrameIndex = m_SwapChain->GetCurrentBackBufferIndex();

		D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc{};
		rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
		rtvHeapDesc.NumDescriptors = frameCount;
		rtvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

		D3D_ASSERT(Context::Get().m_Device->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(m_RTVHeap.GetAddressOf())), "Failed to create D3D12DescriptorHeap!")

		m_RTVDescriptorSize = Context::Get().m_Device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
		CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(m_RTVHeap->GetCPUDescriptorHandleForHeapStart());

		m_RenderTargets.resize(frameCount);
		for (uint32_t i = 0; i < frameCount; i++)
		{
			D3D_ASSERT(m_SwapChain->GetBuffer(i, IID_PPV_ARGS(m_RenderTargets[i].GetAddressOf())), "Failed to GetBuffer from swapchain!")
			Context::Get().m_Device->CreateRenderTargetView(m_RenderTargets[i].Get(), nullptr, rtvHandle);
			rtvHandle.Offset(i, m_RTVDescriptorSize);
		}
	}
}
