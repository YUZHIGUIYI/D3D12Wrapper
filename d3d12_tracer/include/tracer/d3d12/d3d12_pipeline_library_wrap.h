//
// Created by ZZK on 2024/11/24.
//

#pragma once

#include <tracer/common/d3d12_wrap_common.h>

namespace gfxshim
{
	struct ID3D12PipelineLibraryWrapper : ID3D12DeviceChildWrapper
	{
	public:
		ID3D12PipelineLibraryWrapper(REFIID riid, IUnknown *object);

		~ID3D12PipelineLibraryWrapper() override = default;

		virtual HRESULT STDMETHODCALLTYPE StorePipeline(LPCWSTR pName, ID3D12PipelineState *pPipeline);

		virtual HRESULT STDMETHODCALLTYPE LoadGraphicsPipeline(
						LPCWSTR pName,
						const D3D12_GRAPHICS_PIPELINE_STATE_DESC* pDesc,
						REFIID riid,
						void** ppPipelineState);

		virtual HRESULT STDMETHODCALLTYPE LoadComputePipeline(
						LPCWSTR pName,
						const D3D12_COMPUTE_PIPELINE_STATE_DESC* pDesc,
						REFIID riid,
						void** ppPipelineState);

		virtual SIZE_T STDMETHODCALLTYPE GetSerializedSize();

		virtual HRESULT STDMETHODCALLTYPE Serialize(
						void* pData,
						SIZE_T DataSizeInBytes);
	};

	// struct ID3D12PipelineLibrary1Wrapper : ID3D12PipelineLibraryWrapper
	// {
	// public:
	// 	ID3D12PipelineLibrary1Wrapper(REFIID riid, IUnknown *object);
	//
	// 	~ID3D12PipelineLibrary1Wrapper() override = default;
	//
	// 	virtual HRESULT STDMETHODCALLTYPE LoadPipeline(
	// 					LPCWSTR pName,
	// 					const D3D12_PIPELINE_STATE_STREAM_DESC* pDesc,
	// 					REFIID riid,
	// 					void** ppPipelineState);
	// };

	struct ID3D12PipelineLibrary1Wrapper final : ID3D12PipelineLibrary1
	{
		private:
		using IUnknownPtr = _com_ptr_t<_com_IIID<IUnknown, &__uuidof(IUnknown)>>;
		IID m_riid;
		IUnknownPtr m_object;
		std::atomic_uint32_t m_ref_count;

		inline static std::unordered_map<void *, ID3D12PipelineLibrary1Wrapper *> s_d3d12_pipeline_library_manager{};
		inline static std::mutex s_d3d12_pipeline_library_mutex{};

	public:
		ID3D12PipelineLibrary1Wrapper(REFIID riid, IUnknown *object);

		virtual ~ID3D12PipelineLibrary1Wrapper() = default;

		// ID3D12CommandAllocatorWrapper manager
		static void InsertD3D12PipelineLibrary(void *object_key, ID3D12PipelineLibrary1Wrapper *pipeline_library)
		{
			std::lock_guard guard{ s_d3d12_pipeline_library_mutex };
			s_d3d12_pipeline_library_manager[object_key] = pipeline_library;
		}

		static ID3D12PipelineLibrary1Wrapper *QueryExistingD3D12PipelineLibrary(void *object_key)
		{
			std::lock_guard guard{ s_d3d12_pipeline_library_mutex };
			if (s_d3d12_pipeline_library_manager.contains(object_key))
			{
				return s_d3d12_pipeline_library_manager[object_key];
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

		// ID3D12PipelineLibrary
		HRESULT STDMETHODCALLTYPE StorePipeline(LPCWSTR pName, ID3D12PipelineState *pPipeline) override;

		HRESULT STDMETHODCALLTYPE LoadGraphicsPipeline(
						LPCWSTR pName,
						const D3D12_GRAPHICS_PIPELINE_STATE_DESC* pDesc,
						REFIID riid,
						void** ppPipelineState) override;

		HRESULT STDMETHODCALLTYPE LoadComputePipeline(
						LPCWSTR pName,
						const D3D12_COMPUTE_PIPELINE_STATE_DESC* pDesc,
						REFIID riid,
						void** ppPipelineState) override;

		SIZE_T STDMETHODCALLTYPE GetSerializedSize() override;

		HRESULT STDMETHODCALLTYPE Serialize(
						void* pData,
						SIZE_T DataSizeInBytes) override;

		// ID3D12PipelineLibrary1
		HRESULT STDMETHODCALLTYPE LoadPipeline(
				LPCWSTR pName,
				const D3D12_PIPELINE_STATE_STREAM_DESC* pDesc,
				REFIID riid,
				void** ppPipelineState) override;
	};
}
