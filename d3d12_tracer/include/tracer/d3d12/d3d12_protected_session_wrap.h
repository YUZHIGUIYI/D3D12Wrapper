//
// Created by ZZK on 2024/11/23.
//

#pragma once

#include <tracer/common/d3d12_wrap_common.h>

namespace gfxshim
{
	struct ID3D12ProtectedSessionWrapper : ID3D12DeviceChildWrapper
	{
	public:
		ID3D12ProtectedSessionWrapper(REFIID riid, IUnknown *object);

		~ID3D12ProtectedSessionWrapper() override = default;

		virtual HRESULT STDMETHODCALLTYPE GetStatusFence(REFIID riid, void** ppFence);

		virtual D3D12_PROTECTED_SESSION_STATUS STDMETHODCALLTYPE GetSessionStatus();
	};

	struct ID3D12ProtectedResourceSessionWrapper : ID3D12ProtectedSessionWrapper
	{
	public:
		ID3D12ProtectedResourceSessionWrapper(REFIID riid, IUnknown *object);

		~ID3D12ProtectedResourceSessionWrapper() override = default;

		virtual D3D12_PROTECTED_RESOURCE_SESSION_DESC STDMETHODCALLTYPE GetDesc();
	};

	struct ID3D12ProtectedResourceSession1Wrapper : ID3D12ProtectedResourceSessionWrapper
	{
	public:
		ID3D12ProtectedResourceSession1Wrapper(REFIID riid, IUnknown *object);

		~ID3D12ProtectedResourceSession1Wrapper() override = default;

		virtual D3D12_PROTECTED_RESOURCE_SESSION_DESC1 STDMETHODCALLTYPE GetDesc1();
	};
}