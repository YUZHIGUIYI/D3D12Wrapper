//
// Created by ZZK on 2024/11/23.
//

#pragma once

#include <tracer/common/d3d12_wrap_common.h>

namespace gfxshim
{
	struct ID3D12ResourceWrapper : ID3D12PageableWrapper
	{
	public:
		ID3D12ResourceWrapper(REFIID riid, IUnknown *object);

		~ID3D12ResourceWrapper() override = default;

		virtual HRESULT STDMETHODCALLTYPE Map(
						UINT Subresource,
						const D3D12_RANGE* pReadRange,
						void** ppData);

		virtual void STDMETHODCALLTYPE Unmap(
					UINT Subresource,
					const D3D12_RANGE* pWrittenRange);

		virtual D3D12_RESOURCE_DESC STDMETHODCALLTYPE GetDesc();

		virtual D3D12_GPU_VIRTUAL_ADDRESS STDMETHODCALLTYPE GetGPUVirtualAddress();

		virtual HRESULT STDMETHODCALLTYPE WriteToSubresource(
						UINT DstSubresource,
						const D3D12_BOX* pDstBox,
						const void* pSrcData,
						UINT SrcRowPitch,
						UINT SrcDepthPitch);

		virtual HRESULT STDMETHODCALLTYPE ReadFromSubresource(
						void* pDstData,
						UINT DstRowPitch,
						UINT DstDepthPitch,
						UINT SrcSubresource,
						const D3D12_BOX* pSrcBox);

		virtual HRESULT STDMETHODCALLTYPE GetHeapProperties(
						D3D12_HEAP_PROPERTIES* pHeapProperties,
						D3D12_HEAP_FLAGS* pHeapFlags);
	};

	struct ID3D12Resource1Wrapper : ID3D12ResourceWrapper
	{
	public:
		ID3D12Resource1Wrapper(REFIID riid, IUnknown *object);

		~ID3D12Resource1Wrapper() override = default;

		virtual HRESULT STDMETHODCALLTYPE GetProtectedResourceSession(REFIID riid, void** ppProtectedSession);
	};

	// struct ID3D12Resource2Wrapper : ID3D12Resource1Wrapper
	// {
	// public:
	// 	ID3D12Resource2Wrapper(REFIID riid, IUnknown *object);
	//
	// 	~ID3D12Resource2Wrapper() override = default;
	//
	// 	virtual D3D12_RESOURCE_DESC1 STDMETHODCALLTYPE GetDesc1();
	// };
	// New wrapped ID3D12Resource2
	struct ID3D12Resource2Wrapper final : ID3D12Resource2
	{
	private:
		using IUnknownPtr = _com_ptr_t<_com_IIID<IUnknown, &__uuidof(IUnknown)>>;
		IID m_riid;
		IUnknownPtr m_object;
		std::atomic_uint32_t m_ref_count;

		inline static std::unordered_map<void *, ID3D12Resource2Wrapper *> s_d3d12_resource_manager{};
		inline static std::mutex s_d3d12_resource_mutex{};

	public:
		ID3D12Resource2Wrapper(REFIID riid, IUnknown *object);

		virtual ~ID3D12Resource2Wrapper() = default;

		// ID3D12Resource2Wrapper manager
		static void InsertD3D12Resource(void *object_key, ID3D12Resource2Wrapper *resource)
		{
			std::lock_guard guard{ s_d3d12_resource_mutex };
			s_d3d12_resource_manager[object_key] = resource;
		}

		static ID3D12Resource2Wrapper *QueryExistingD3D12Resource(void *object_key)
		{
			std::lock_guard guard{ s_d3d12_resource_mutex };
			if (s_d3d12_resource_manager.contains(object_key))
			{
				return s_d3d12_resource_manager[object_key];
			}
			return nullptr;
		}

		// Helper functions
		REFIID GetRiid() const;

		IUnknown *GetWrappedObject();

		const IUnknown *GetWrappedObject() const;

		template <typename T>
		T *GetWrappedObjectAs()
		{
			return reinterpret_cast<T *>(m_object.GetInterfacePtr());
		}

		template <typename T>
		const T *GetWrappedObjectAs() const
		{
			return reinterpret_cast<const T *>(m_object.GetInterfacePtr());
		}

		uint32_t GetRefCount() const;

		// IUnknown
		HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** object) override;

		ULONG STDMETHODCALLTYPE AddRef() override;

		ULONG STDMETHODCALLTYPE Release() override;

		// ID3D12Object
		HRESULT STDMETHODCALLTYPE GetPrivateData(REFGUID guid, UINT* pDataSize, void* pData) override;

		HRESULT STDMETHODCALLTYPE SetPrivateData(REFGUID guid, UINT DataSize, const void* pData) override;

		HRESULT STDMETHODCALLTYPE SetPrivateDataInterface(REFGUID guid, const IUnknown* pData) override;

		HRESULT STDMETHODCALLTYPE SetName(LPCWSTR Name) override;

		// ID3D12DeviceChild
		HRESULT STDMETHODCALLTYPE GetDevice(REFIID riid, void** ppvDevice) override;

		// ID3D12Resource
		HRESULT STDMETHODCALLTYPE Map(
						UINT Subresource,
						const D3D12_RANGE* pReadRange,
						void** ppData) override;

		void STDMETHODCALLTYPE Unmap(
					UINT Subresource,
					const D3D12_RANGE* pWrittenRange) override;

		D3D12_RESOURCE_DESC STDMETHODCALLTYPE GetDesc() override;

		D3D12_GPU_VIRTUAL_ADDRESS STDMETHODCALLTYPE GetGPUVirtualAddress() override;

		HRESULT STDMETHODCALLTYPE WriteToSubresource(
						UINT DstSubresource,
						const D3D12_BOX* pDstBox,
						const void* pSrcData,
						UINT SrcRowPitch,
						UINT SrcDepthPitch) override;

		HRESULT STDMETHODCALLTYPE ReadFromSubresource(
						void* pDstData,
						UINT DstRowPitch,
						UINT DstDepthPitch,
						UINT SrcSubresource,
						const D3D12_BOX* pSrcBox) override;

		HRESULT STDMETHODCALLTYPE GetHeapProperties(
						D3D12_HEAP_PROPERTIES* pHeapProperties,
						D3D12_HEAP_FLAGS* pHeapFlags) override;

		// ID3D12Resource1
		HRESULT STDMETHODCALLTYPE GetProtectedResourceSession(REFIID riid, void** ppProtectedSession) override;

		// ID3D12Resource2
		D3D12_RESOURCE_DESC1 STDMETHODCALLTYPE GetDesc1() override;
	};
}
