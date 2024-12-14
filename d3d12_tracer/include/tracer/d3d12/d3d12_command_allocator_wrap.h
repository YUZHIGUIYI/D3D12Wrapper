//
// Created by ZZK on 2024/7/21.
//

#pragma once

#include <tracer/common/d3d12_wrap_common.h>

namespace gfxshim
{
	// New wrapped ID3D12CommandAllocator
	struct ID3D12CommandAllocatorWrapper final : ID3D12CommandAllocator
	{
	private:
		using IUnknownPtr = _com_ptr_t<_com_IIID<IUnknown, &__uuidof(IUnknown)>>;
		IID m_riid;
		IUnknownPtr m_object;
		std::atomic_uint32_t m_ref_count;

		inline static std::unordered_map<void *, ID3D12CommandAllocatorWrapper *> s_d3d12_command_allocator_manager{};
		inline static std::mutex s_d3d12_command_allocator_mutex{};

	public:
		ID3D12CommandAllocatorWrapper(REFIID riid, IUnknown *object);

		virtual ~ID3D12CommandAllocatorWrapper() = default;

		// ID3D12CommandAllocatorWrapper manager
		static void InsertD3D12CommandAllocator(void *object_key, ID3D12CommandAllocatorWrapper *command_allocator)
		{
			std::lock_guard guard{ s_d3d12_command_allocator_mutex };
			s_d3d12_command_allocator_manager[object_key] = command_allocator;
		}

		static ID3D12CommandAllocatorWrapper *QueryExistingD3D12CommandAllocator(void *object_key)
		{
			std::lock_guard guard{ s_d3d12_command_allocator_mutex };
			if (s_d3d12_command_allocator_manager.contains(object_key))
			{
				return s_d3d12_command_allocator_manager[object_key];
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

		// ID3D12Pageable

		// ID3D12CommandAllocator
		HRESULT STDMETHODCALLTYPE Reset() override;
	};
}

class WrappedID3D12Device;

class WrappedID3D12CommandAllocator : public ID3D12CommandAllocator
{
private:
    ID3D12CommandAllocator *m_command_allocator = nullptr;
    WrappedID3D12Device *m_wrapped_device = nullptr;

public:
    WrappedID3D12CommandAllocator(ID3D12CommandAllocator *real_command_allocator, WrappedID3D12Device *wrapped_device);

    virtual ~WrappedID3D12CommandAllocator();

    [[nodiscard]] ID3D12CommandAllocator *GetReal() const;

    // Implement IUnknown
    ULONG STDMETHODCALLTYPE AddRef() final;

    ULONG STDMETHODCALLTYPE Release() final;

    HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void **ppvObject) final;

    // Implement ID3D12Object
    HRESULT STDMETHODCALLTYPE GetPrivateData(REFGUID guid, UINT *pDataSize, void *pData) final;

    HRESULT STDMETHODCALLTYPE SetPrivateData(REFGUID guid, UINT DataSize, const void *pData) final;

    HRESULT STDMETHODCALLTYPE SetPrivateDataInterface(REFGUID guid, const IUnknown *pData) final;

    HRESULT STDMETHODCALLTYPE SetName(LPCWSTR Name) final;

    // Implement ID3D12DeviceChild
    HRESULT STDMETHODCALLTYPE GetDevice(REFIID riid, void** ppvDevice) final;

    // Implement ID3D12CommandAllocator
    HRESULT STDMETHODCALLTYPE Reset() final;
};
