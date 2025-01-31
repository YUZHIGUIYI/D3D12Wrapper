//
// Created by ZZK on 2024/11/23.
//

#pragma once

#include <tracer/common/d3d12_wrap_common.h>

namespace gfxshim
{
	// New wrapped ID3D12Heap1
	struct ID3D12Heap1Wrapper final : ID3D12Heap1
	{
	private:
		using IUnknownPtr = _com_ptr_t<_com_IIID<IUnknown, &__uuidof(IUnknown)>>;
		IID m_riid;
		IUnknownPtr m_object;
		std::atomic_uint32_t m_ref_count;

		inline static std::unordered_map<void *, ID3D12Heap1Wrapper *> s_d3d12_heap_manager{};
		inline static std::mutex s_d3d12_heap_mutex{};

	public:
		ID3D12Heap1Wrapper(REFIID riid, IUnknown *object);

		virtual ~ID3D12Heap1Wrapper() = default;

		// ID3D12Heap1Wrapper manager
		static void InsertD3D12Heap(void *object_key, ID3D12Heap1Wrapper *heap)
		{
			std::lock_guard guard{ s_d3d12_heap_mutex };
			s_d3d12_heap_manager[object_key] = heap;
		}

		static ID3D12Heap1Wrapper *QueryExistingD3D12Heap(void *object_key)
		{
			std::lock_guard guard{ s_d3d12_heap_mutex };
			if (s_d3d12_heap_manager.contains(object_key))
			{
				return s_d3d12_heap_manager[object_key];
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

		// ID3D12Heap
		D3D12_HEAP_DESC STDMETHODCALLTYPE GetDesc() override;

		// ID3D12Heap1
		HRESULT STDMETHODCALLTYPE GetProtectedResourceSession(REFIID riid, void** ppProtectedSession) override;
	};

	struct ID3D12DescriptorHeapWrapper final : ID3D12DescriptorHeap
	{
	private:
		using IUnknownPtr = _com_ptr_t<_com_IIID<IUnknown, &__uuidof(IUnknown)>>;
		IID m_riid;
		IUnknownPtr m_object;
		std::atomic_uint32_t m_ref_count;

		inline static std::unordered_map<void *, ID3D12DescriptorHeapWrapper *> s_d3d12_descriptor_heap_manager{};
		inline static std::mutex s_d3d12_descriptor_heap_mutex{};

	public:
		ID3D12DescriptorHeapWrapper(REFIID riid, IUnknown *object);

		virtual ~ID3D12DescriptorHeapWrapper() = default;

		// ID3D12DescriptorHeapWrapper manager
		static void InsertD3D12DescriptorHeap(void *object_key, ID3D12DescriptorHeapWrapper *descriptor_heap)
		{
			std::lock_guard guard{ s_d3d12_descriptor_heap_mutex };
			s_d3d12_descriptor_heap_manager[object_key] = descriptor_heap;
		}

		static ID3D12DescriptorHeapWrapper *QueryExistingD3D12DescriptorHeap(void *object_key)
		{
			std::lock_guard guard{ s_d3d12_descriptor_heap_mutex };
			if (s_d3d12_descriptor_heap_manager.contains(object_key))
			{
				return s_d3d12_descriptor_heap_manager[object_key];
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

		// ID3D12DescriptorHeap
		D3D12_DESCRIPTOR_HEAP_DESC STDMETHODCALLTYPE GetDesc() override;

		D3D12_CPU_DESCRIPTOR_HANDLE STDMETHODCALLTYPE GetCPUDescriptorHandleForHeapStart() override;

		D3D12_GPU_DESCRIPTOR_HANDLE STDMETHODCALLTYPE GetGPUDescriptorHandleForHeapStart() override;
	};

	struct ID3D12QueryHeapWrapper final : ID3D12QueryHeap
	{
	private:
		using IUnknownPtr = _com_ptr_t<_com_IIID<IUnknown, &__uuidof(IUnknown)>>;
		IID m_riid;
		IUnknownPtr m_object;
		std::atomic_uint32_t m_ref_count;

		inline static std::unordered_map<void *, ID3D12QueryHeapWrapper *> s_d3d12_query_heap_manager{};
		inline static std::mutex s_d3d12_query_heap_mutex{};

	public:
		ID3D12QueryHeapWrapper(REFIID riid, IUnknown *object);

		virtual ~ID3D12QueryHeapWrapper() = default;

		// ID3D12QueryHeapWrapper manager
		static void InsertD3D12QueryHeap(void *object_key, ID3D12QueryHeapWrapper *descriptor_heap)
		{
			std::lock_guard guard{ s_d3d12_query_heap_mutex };
			s_d3d12_query_heap_manager[object_key] = descriptor_heap;
		}

		static ID3D12QueryHeapWrapper *QueryExistingD3D12QueryHeap(void *object_key)
		{
			std::lock_guard guard{ s_d3d12_query_heap_mutex };
			if (s_d3d12_query_heap_manager.contains(object_key))
			{
				return s_d3d12_query_heap_manager[object_key];
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
	};
}
