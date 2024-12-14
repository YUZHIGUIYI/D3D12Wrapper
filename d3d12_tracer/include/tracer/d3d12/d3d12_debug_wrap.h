//
// Created by ZZK on 2024/11/23.
//

#pragma once

#include <tracer/common/d3d12_wrap_common.h>

namespace gfxshim
{
	struct ID3D12DebugWrapper : IUnknownWrapper
	{
	public:
		ID3D12DebugWrapper(REFIID riid, IUnknown *object);

		~ID3D12DebugWrapper() override = default;

		virtual void STDMETHODCALLTYPE EnableDebugLayer();
	};

	struct ID3D12Debug1Wrapper final : ID3D12Debug1
	{
	private:
		using IUnknownPtr = _com_ptr_t<_com_IIID<IUnknown, &__uuidof(IUnknown)>>;
		IID m_riid;
		IUnknownPtr m_object;
		std::atomic_uint32_t m_ref_count;

		inline static std::unordered_map<void *, ID3D12Debug1Wrapper *> s_d3d12_debug1_manager{};
		inline static std::mutex s_d3d12_debug1_mutex{};

	public:
		ID3D12Debug1Wrapper(REFIID riid, IUnknown *object);

		virtual ~ID3D12Debug1Wrapper() = default;

		// ID3D12Debug1Wrapper manager
		static void InsertD3D12Debug1(void *object_key, ID3D12Debug1Wrapper *debug1)
		{
			std::lock_guard guard{ s_d3d12_debug1_mutex };
			s_d3d12_debug1_manager[object_key] = debug1;
		}

		static ID3D12Debug1Wrapper *QueryExistingD3D12Debug1(void *object_key)
		{
			std::lock_guard guard{ s_d3d12_debug1_mutex };
			if (s_d3d12_debug1_manager.contains(object_key))
			{
				return s_d3d12_debug1_manager[object_key];
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

		// ID3D12Debug1
		void STDMETHODCALLTYPE EnableDebugLayer() override;

		void STDMETHODCALLTYPE SetEnableGPUBasedValidation(BOOL Enable) override;

		void STDMETHODCALLTYPE SetEnableSynchronizedCommandQueueValidation(BOOL Enable) override;
	};

	struct ID3D12Debug2Wrapper final : ID3D12Debug2
	{
	private:
		using IUnknownPtr = _com_ptr_t<_com_IIID<IUnknown, &__uuidof(IUnknown)>>;
		IID m_riid;
		IUnknownPtr m_object;
		std::atomic_uint32_t m_ref_count;

		inline static std::unordered_map<void *, ID3D12Debug2Wrapper *> s_d3d12_debug2_manager{};
		inline static std::mutex s_d3d12_debug2_mutex{};

	public:
		ID3D12Debug2Wrapper(REFIID riid, IUnknown *object);

		virtual ~ID3D12Debug2Wrapper() = default;

		// ID3D12Debug2Wrapper manager
		static void InsertD3D12Debug2(void *object_key, ID3D12Debug2Wrapper *command_allocator)
		{
			std::lock_guard guard{ s_d3d12_debug2_mutex };
			s_d3d12_debug2_manager[object_key] = command_allocator;
		}

		static ID3D12Debug2Wrapper *QueryExistingD3D12Debug2(void *object_key)
		{
			std::lock_guard guard{ s_d3d12_debug2_mutex };
			if (s_d3d12_debug2_manager.contains(object_key))
			{
				return s_d3d12_debug2_manager[object_key];
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

		// ID3D12Debug2
		void STDMETHODCALLTYPE SetGPUBasedValidationFlags(D3D12_GPU_BASED_VALIDATION_FLAGS Flags) override;
	};

	struct ID3D12Debug3Wrapper : ID3D12DebugWrapper
	{
	public:
		ID3D12Debug3Wrapper(REFIID riid, IUnknown *object);

		~ID3D12Debug3Wrapper() override = default;

		virtual void STDMETHODCALLTYPE SetEnableGPUBasedValidation(BOOL Enable);

		virtual void STDMETHODCALLTYPE SetEnableSynchronizedCommandQueueValidation(BOOL Enable);

		virtual void STDMETHODCALLTYPE SetGPUBasedValidationFlags(D3D12_GPU_BASED_VALIDATION_FLAGS Flags);
	};

	struct ID3D12Debug4Wrapper : ID3D12Debug3Wrapper
	{
	public:
		ID3D12Debug4Wrapper(REFIID riid, IUnknown *object);

		~ID3D12Debug4Wrapper() override = default;

		virtual void STDMETHODCALLTYPE DisableDebugLayer();
	};

	struct ID3D12Debug5Wrapper : ID3D12Debug4Wrapper
	{
	public:
		ID3D12Debug5Wrapper(REFIID riid, IUnknown *object);

		~ID3D12Debug5Wrapper() override = default;

		virtual void STDMETHODCALLTYPE SetEnableAutoName(BOOL Enable);
	};

	struct ID3D12Debug6Wrapper final : ID3D12Debug6
	{
	private:
		using IUnknownPtr = _com_ptr_t<_com_IIID<IUnknown, &__uuidof(IUnknown)>>;
		IID m_riid;
		IUnknownPtr m_object;
		std::atomic_uint32_t m_ref_count;

		inline static std::unordered_map<void *, ID3D12Debug6Wrapper *> s_d3d12_debug_manager{};
		inline static std::mutex s_d3d12_debug_mutex{};

	public:
		ID3D12Debug6Wrapper(REFIID riid, IUnknown *object);

		virtual ~ID3D12Debug6Wrapper() = default;

		// ID3D12Debug6Wrapper manager
		static void InsertD3D12Debug6(void *object_key, ID3D12Debug6Wrapper *debug6)
		{
			std::lock_guard guard{ s_d3d12_debug_mutex };
			s_d3d12_debug_manager[object_key] = debug6;
		}

		static ID3D12Debug6Wrapper *QueryExistingD3D12Debug6(void *object_key)
		{
			std::lock_guard guard{ s_d3d12_debug_mutex };
			if (s_d3d12_debug_manager.contains(object_key))
			{
				return s_d3d12_debug_manager[object_key];
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

		// ID3D12Debug
		void STDMETHODCALLTYPE EnableDebugLayer() override;

		// ID3D12Debug3
		void STDMETHODCALLTYPE SetEnableGPUBasedValidation(BOOL Enable) override;

		void STDMETHODCALLTYPE SetEnableSynchronizedCommandQueueValidation(BOOL Enable) override;

		void STDMETHODCALLTYPE SetGPUBasedValidationFlags(D3D12_GPU_BASED_VALIDATION_FLAGS Flags) override;

		// ID3D12Debug4
		void STDMETHODCALLTYPE DisableDebugLayer() override;

		// ID3D12Debug5
		void STDMETHODCALLTYPE SetEnableAutoName(BOOL Enable) override;

		// ID3D12Debug6
		void STDMETHODCALLTYPE SetForceLegacyBarrierValidation(BOOL Enable) override;
	};

	struct ID3D12DebugDeviceWrapper : IUnknownWrapper
	{
	public:
		ID3D12DebugDeviceWrapper(REFIID riid, IUnknown *object);

		~ID3D12DebugDeviceWrapper() override = default;

		virtual HRESULT STDMETHODCALLTYPE SetFeatureMask(D3D12_DEBUG_FEATURE Mask);

		virtual D3D12_DEBUG_FEATURE STDMETHODCALLTYPE GetFeatureMask();

		virtual HRESULT STDMETHODCALLTYPE ReportLiveDeviceObjects(D3D12_RLDO_FLAGS Flags);
	};

	struct ID3D12DebugDevice1Wrapper final : ID3D12DebugDevice1
	{
	private:
		using IUnknownPtr = _com_ptr_t<_com_IIID<IUnknown, &__uuidof(IUnknown)>>;
		IID m_riid;
		IUnknownPtr m_object;
		std::atomic_uint32_t m_ref_count;

		inline static std::unordered_map<void *, ID3D12DebugDevice1Wrapper *> s_d3d12_debug_device1_manager{};
		inline static std::mutex s_d3d12_debug_device1_mutex{};

	public:
		ID3D12DebugDevice1Wrapper(REFIID riid, IUnknown *object);

		virtual ~ID3D12DebugDevice1Wrapper() = default;

		// ID3D12DebugDevice1Wrapper manager
		static void InsertD3D12DebugDevice1(void *object_key, ID3D12DebugDevice1Wrapper *debug_device1)
		{
			std::lock_guard guard{ s_d3d12_debug_device1_mutex };
			s_d3d12_debug_device1_manager[object_key] = debug_device1;
		}

		static ID3D12DebugDevice1Wrapper *QueryExistingD3D12DebugDevice1(void *object_key)
		{
			std::lock_guard guard{ s_d3d12_debug_device1_mutex };
			if (s_d3d12_debug_device1_manager.contains(object_key))
			{
				return s_d3d12_debug_device1_manager[object_key];
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

		// ID3D12DebugDevice1
		virtual HRESULT STDMETHODCALLTYPE SetDebugParameter(D3D12_DEBUG_DEVICE_PARAMETER_TYPE Type, const void* pData, UINT DataSize);

		virtual HRESULT STDMETHODCALLTYPE GetDebugParameter(D3D12_DEBUG_DEVICE_PARAMETER_TYPE Type, void* pData, UINT DataSize);

		virtual HRESULT STDMETHODCALLTYPE ReportLiveDeviceObjects(D3D12_RLDO_FLAGS Flags);
	};

	struct ID3D12DebugDevice2Wrapper final : ID3D12DebugDevice2
	{
	private:
		using IUnknownPtr = _com_ptr_t<_com_IIID<IUnknown, &__uuidof(IUnknown)>>;
		IID m_riid;
		IUnknownPtr m_object;
		std::atomic_uint32_t m_ref_count;

		inline static std::unordered_map<void *, ID3D12DebugDevice2Wrapper *> s_d3d12_debug_device2_manager{};
		inline static std::mutex s_d3d12_debug_device2_mutex{};

	public:
		ID3D12DebugDevice2Wrapper(REFIID riid, IUnknown *object);

		virtual ~ID3D12DebugDevice2Wrapper() = default;

		// ID3D12DebugDevice2Wrapper manager
		static void InsertD3D12DebugDevice2(void *object_key, ID3D12DebugDevice2Wrapper *debug_device2)
		{
			std::lock_guard guard{ s_d3d12_debug_device2_mutex };
			s_d3d12_debug_device2_manager[object_key] = debug_device2;
		}

		static ID3D12DebugDevice2Wrapper *QueryExistingD3D12DebugDevice2(void *object_key)
		{
			std::lock_guard guard{ s_d3d12_debug_device2_mutex };
			if (s_d3d12_debug_device2_manager.contains(object_key))
			{
				return s_d3d12_debug_device2_manager[object_key];
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

		// ID3D12DebugDevice
		HRESULT STDMETHODCALLTYPE SetFeatureMask(D3D12_DEBUG_FEATURE Mask) override;

		D3D12_DEBUG_FEATURE STDMETHODCALLTYPE GetFeatureMask() override;

		HRESULT STDMETHODCALLTYPE ReportLiveDeviceObjects(D3D12_RLDO_FLAGS Flags) override;

		// ID3D12DebugDevice2
		HRESULT STDMETHODCALLTYPE SetDebugParameter(D3D12_DEBUG_DEVICE_PARAMETER_TYPE Type, const void* pData, UINT DataSize) override;

		HRESULT STDMETHODCALLTYPE GetDebugParameter(D3D12_DEBUG_DEVICE_PARAMETER_TYPE Type, void* pData, UINT DataSize) override;
	};

	struct ID3D12DebugCommandQueueWrapper : IUnknownWrapper
	{
	public:
		ID3D12DebugCommandQueueWrapper(REFIID riid, IUnknown *object);

		~ID3D12DebugCommandQueueWrapper() override = default;

		virtual BOOL STDMETHODCALLTYPE AssertResourceState(ID3D12Resource* pResource, UINT Subresource, UINT State);
	};

	struct ID3D12DebugCommandQueue1Wrapper final : ID3D12DebugCommandQueue1
	{
	private:
		using IUnknownPtr = _com_ptr_t<_com_IIID<IUnknown, &__uuidof(IUnknown)>>;
		IID m_riid;
		IUnknownPtr m_object;
		std::atomic_uint32_t m_ref_count;

		inline static std::unordered_map<void *, ID3D12DebugCommandQueue1Wrapper *> s_d3d12_debug_queue_manager{};
		inline static std::mutex s_d3d12_debug_queue_mutex{};

	public:
		ID3D12DebugCommandQueue1Wrapper(REFIID riid, IUnknown *object);

		virtual ~ID3D12DebugCommandQueue1Wrapper() = default;

		// ID3D12DebugCommandQueue1Wrapper manager
		static void InsertD3D12DebugCommandQueue(void *object_key, ID3D12DebugCommandQueue1Wrapper *debug_queue1)
		{
			std::lock_guard guard{ s_d3d12_debug_queue_mutex };
			s_d3d12_debug_queue_manager[object_key] = debug_queue1;
		}

		static ID3D12DebugCommandQueue1Wrapper *QueryExistingD3D12DebugCommandQueue(void *object_key)
		{
			std::lock_guard guard{ s_d3d12_debug_queue_mutex };
			if (s_d3d12_debug_queue_manager.contains(object_key))
			{
				return s_d3d12_debug_queue_manager[object_key];
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

		// ID3D12DebugCommandQueue
		BOOL STDMETHODCALLTYPE AssertResourceState(ID3D12Resource* pResource, UINT Subresource, UINT State) override;

		// ID3D12DebugCommandQueue1
		void STDMETHODCALLTYPE AssertResourceAccess(ID3D12Resource* pResource, UINT Subresource, D3D12_BARRIER_ACCESS Access) override;

		void STDMETHODCALLTYPE AssertTextureLayout(ID3D12Resource* pResource, UINT Subresource, D3D12_BARRIER_LAYOUT Layout) override;
	};

	struct ID3D12DebugCommandListWrapper : IUnknownWrapper
	{
	public:
		ID3D12DebugCommandListWrapper(REFIID riid, IUnknown *object);

		~ID3D12DebugCommandListWrapper() override = default;

		virtual BOOL STDMETHODCALLTYPE AssertResourceState(ID3D12Resource* pResource, UINT Subresource, UINT State);

		virtual HRESULT STDMETHODCALLTYPE SetFeatureMask(D3D12_DEBUG_FEATURE Mask);

		virtual D3D12_DEBUG_FEATURE STDMETHODCALLTYPE GetFeatureMask();
	};

	struct ID3D12DebugCommandList1Wrapper final : ID3D12DebugCommandList1
	{
	private:
		using IUnknownPtr = _com_ptr_t<_com_IIID<IUnknown, &__uuidof(IUnknown)>>;
		IID m_riid;
		IUnknownPtr m_object;
		std::atomic_uint32_t m_ref_count;

		inline static std::unordered_map<void *, ID3D12DebugCommandList1Wrapper *> s_d3d12_debug_command_list1_manager{};
		inline static std::mutex s_d3d12_debug_command_list1_mutex{};

	public:
		ID3D12DebugCommandList1Wrapper(REFIID riid, IUnknown *object);

		virtual ~ID3D12DebugCommandList1Wrapper() = default;

		// ID3D12DebugCommandList1Wrapper manager
		static void InsertD3D12DebugCommandList1(void *object_key, ID3D12DebugCommandList1Wrapper *command_allocator)
		{
			std::lock_guard guard{ s_d3d12_debug_command_list1_mutex };
			s_d3d12_debug_command_list1_manager[object_key] = command_allocator;
		}

		static ID3D12DebugCommandList1Wrapper *QueryExistingD3D12DebugCommandList1(void *object_key)
		{
			std::lock_guard guard{ s_d3d12_debug_command_list1_mutex };
			if (s_d3d12_debug_command_list1_manager.contains(object_key))
			{
				return s_d3d12_debug_command_list1_manager[object_key];
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

		// ID3D12DebugCommandList1
		BOOL STDMETHODCALLTYPE AssertResourceState(ID3D12Resource* pResource, UINT Subresource, UINT State) override;

		HRESULT STDMETHODCALLTYPE SetDebugParameter(
						D3D12_DEBUG_COMMAND_LIST_PARAMETER_TYPE Type,
						const void* pData,
						UINT DataSize) override;

		HRESULT STDMETHODCALLTYPE GetDebugParameter(
						D3D12_DEBUG_COMMAND_LIST_PARAMETER_TYPE Type,
						void* pData,
						UINT DataSize) override;
	};

	struct ID3D12DebugCommandList2Wrapper : ID3D12DebugCommandListWrapper
	{
	public:
		ID3D12DebugCommandList2Wrapper(REFIID riid, IUnknown *object);

		~ID3D12DebugCommandList2Wrapper() override = default;

		virtual HRESULT STDMETHODCALLTYPE SetDebugParameter(
						D3D12_DEBUG_COMMAND_LIST_PARAMETER_TYPE Type,
						const void* pData,
						UINT DataSize);

		virtual HRESULT STDMETHODCALLTYPE GetDebugParameter(
						D3D12_DEBUG_COMMAND_LIST_PARAMETER_TYPE Type,
						void* pData,
						UINT DataSize);
	};

	struct ID3D12DebugCommandList3Wrapper final : ID3D12DebugCommandList3
	{
	private:
		using IUnknownPtr = _com_ptr_t<_com_IIID<IUnknown, &__uuidof(IUnknown)>>;
		IID m_riid;
		IUnknownPtr m_object;
		std::atomic_uint32_t m_ref_count;

		inline static std::unordered_map<void *, ID3D12DebugCommandList3Wrapper *> s_d3d12_debug_command_list3_manager{};
		inline static std::mutex s_d3d12_debug_command_list3_mutex{};

	public:
		ID3D12DebugCommandList3Wrapper(REFIID riid, IUnknown *object);

		virtual ~ID3D12DebugCommandList3Wrapper() = default;

		// ID3D12DebugCommandList3Wrapper manager
		static void InsertD3D12DebugCommandList3(void *object_key, ID3D12DebugCommandList3Wrapper *command_allocator)
		{
			std::lock_guard guard{ s_d3d12_debug_command_list3_mutex };
			s_d3d12_debug_command_list3_manager[object_key] = command_allocator;
		}

		static ID3D12DebugCommandList3Wrapper *QueryExistingD3D12DebugCommandList3(void *object_key)
		{
			std::lock_guard guard{ s_d3d12_debug_command_list3_mutex };
			if (s_d3d12_debug_command_list3_manager.contains(object_key))
			{
				return s_d3d12_debug_command_list3_manager[object_key];
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

		// ID3D12DebugCommandList
		BOOL STDMETHODCALLTYPE AssertResourceState(ID3D12Resource* pResource, UINT Subresource, UINT State) override;

		HRESULT STDMETHODCALLTYPE SetFeatureMask(D3D12_DEBUG_FEATURE Mask) override;

		D3D12_DEBUG_FEATURE STDMETHODCALLTYPE GetFeatureMask() override;

		// ID3D12DebugCommandList2
		HRESULT STDMETHODCALLTYPE SetDebugParameter(
						D3D12_DEBUG_COMMAND_LIST_PARAMETER_TYPE Type,
						const void* pData,
						UINT DataSize) override;

		HRESULT STDMETHODCALLTYPE GetDebugParameter(
						D3D12_DEBUG_COMMAND_LIST_PARAMETER_TYPE Type,
						void* pData,
						UINT DataSize) override;

		// ID3D12DebugCommandList3
		void STDMETHODCALLTYPE AssertResourceAccess(
						ID3D12Resource* pResource,
						UINT Subresource,
						D3D12_BARRIER_ACCESS Access) override;

		void STDMETHODCALLTYPE AssertTextureLayout(
						ID3D12Resource* pResource,
						UINT Subresource,
						D3D12_BARRIER_LAYOUT Layout) override;
	};
}
