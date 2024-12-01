//
// Created by ZZK on 2024/7/17.
//

#pragma once

#include <gfxshim/common/base.h>
#include <tracer/common/logger.h>
#include <comip.h>

namespace gfxshim
{
	template <typename T>
	struct alignas(void *) Dx12SubObjectType
	{
		D3D12_PIPELINE_STATE_SUBOBJECT_TYPE type;
		T value;
	};

	using Dx12UintSubObject				   = Dx12SubObjectType<uint32_t>;
	using Dx12SignatureSubObject		   = Dx12SubObjectType<ID3D12RootSignature *>;
	using Dx12ShaderBytecodeSubObject	   = Dx12SubObjectType<D3D12_SHADER_BYTECODE>;
	using Dx12StreamOutputSubObject		   = Dx12SubObjectType<D3D12_STREAM_OUTPUT_DESC>;
	using Dx12BlendSubObject			   = Dx12SubObjectType<D3D12_BLEND_DESC>;
	using Dx12RasterizerSubObject		   = Dx12SubObjectType<D3D12_RASTERIZER_DESC>;
	using Dx12DepthStencilSubObject		   = Dx12SubObjectType<D3D12_DEPTH_STENCIL_DESC>;
	using Dx12InputLayoutSubObject		   = Dx12SubObjectType<D3D12_INPUT_LAYOUT_DESC>;
	using Dx12StripCutSubObject			   = Dx12SubObjectType<D3D12_INDEX_BUFFER_STRIP_CUT_VALUE>;
	using Dx12PrimitiveTopologySubObject   = Dx12SubObjectType<D3D12_PRIMITIVE_TOPOLOGY_TYPE>;
	using Dx12RenderTargetFormatsSubObject = Dx12SubObjectType<D3D12_RT_FORMAT_ARRAY>;
	using Dx12FormatSubObject			   = Dx12SubObjectType<DXGI_FORMAT>;
	using Dx12SampleDescSubObject          = Dx12SubObjectType<DXGI_SAMPLE_DESC>;
	using Dx12CachedPSOSubObject           = Dx12SubObjectType<D3D12_CACHED_PIPELINE_STATE>;
	using Dx12TypeFlagsSubObject           = Dx12SubObjectType<D3D12_PIPELINE_STATE_FLAGS>;
	using Dx12DepthStencil1SubObject       = Dx12SubObjectType<D3D12_DEPTH_STENCIL_DESC1>;
	using Dx12ViewInstancingSubObject      = Dx12SubObjectType<D3D12_VIEW_INSTANCING_DESC>;

    constexpr IID IID_IUnknown_Wrapper = { 0xe00bb2cc, 0x162e, 0x4aad, { 0x97, 0x69, 0xed, 0xe6, 0x91, 0x53, 0x95, 0xf6 } };

    MIDL_INTERFACE("E00BB2CC-162E-4AAD-9769-EDE6915395F6")
    IUnknownWrapper : IUnknown
    {
    public:
        IUnknownWrapper(REFIID riid, IUnknown *wrapper_object);

        HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** object) override;

        ULONG STDMETHODCALLTYPE AddRef() override;

        ULONG STDMETHODCALLTYPE Release() override;

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

        virtual ~IUnknownWrapper();

    private:
		using IUnknownPtr = _com_ptr_t<_com_IIID<IUnknown, &__uuidof(IUnknown)>>;
        IID m_riid;
        IUnknownPtr m_object;
        std::atomic_uint32_t m_ref_count;
    };

    struct ID3D12ObjectWrapper : IUnknownWrapper
    {
    public:
        ID3D12ObjectWrapper(REFIID riid, IUnknown *object);

        virtual HRESULT STDMETHODCALLTYPE GetPrivateData(
                _In_  REFGUID guid,
                _Inout_  UINT* pDataSize,
                _Out_writes_bytes_opt_(*pDataSize)  void* pData);

        virtual HRESULT STDMETHODCALLTYPE SetPrivateData(
                _In_  REFGUID guid,
                _In_  UINT DataSize,
                _In_reads_bytes_opt_(DataSize)  const void* pData);

        virtual HRESULT STDMETHODCALLTYPE SetPrivateDataInterface(
                _In_  REFGUID guid,
                _In_opt_  const IUnknown* pData);

        virtual HRESULT STDMETHODCALLTYPE SetName(
                _In_z_  LPCWSTR Name);
    };

    struct ID3D12DeviceChildWrapper : ID3D12ObjectWrapper
    {
    public:
        ID3D12DeviceChildWrapper(REFIID riid, IUnknown *object);

        virtual HRESULT STDMETHODCALLTYPE GetDevice(
                REFIID riid,
                void** ppvDevice);
    };

    struct ID3D12PageableWrapper : ID3D12DeviceChildWrapper
    {
    public:
        ID3D12PageableWrapper(REFIID riid, IUnknown *object);
    };

    namespace encode
    {
        template <typename T>
        T *GetWrappedObject(T *wrapped_object)
        {
            if (wrapped_object != nullptr)
            {
				return reinterpret_cast<IUnknownWrapper *>(wrapped_object)->GetWrappedObjectAs<T>();
            }
			return nullptr;
        }

        template <typename T>
        const T *GetWrappedObject(const T *wrapped_object)
        {
            if (wrapped_object != nullptr)
            {
	            return reinterpret_cast<const IUnknownWrapper *>(wrapped_object)->GetWrappedObjectAs<T>();
            }
			return nullptr;
        }

		template <>
		inline IUnknown *GetWrappedObject<IUnknown>(IUnknown *wrapped_object)
		{
			IUnknown *object = wrapped_object;
			IUnknownWrapper *wrapper = nullptr;
			if (object != nullptr &&
				SUCCEEDED(object->QueryInterface(IID_IUnknown_Wrapper, reinterpret_cast<void **>(&wrapper))))
			{
				object = wrapper->GetWrappedObject();
			}
			return object;
		}

		template <>
		inline const IUnknown *GetWrappedObject<IUnknown>(const IUnknown *wrapped_object)
		{
			auto *object = const_cast<IUnknown *>(wrapped_object);
			IUnknownWrapper *wrapper = nullptr;
			if (object != nullptr &&
				SUCCEEDED(object->QueryInterface(IID_IUnknown_Wrapper, reinterpret_cast<void **>(&wrapper))))
			{
				object = wrapper->GetWrappedObject();
			}
			return object;
		}

		void UnwrapStructObjects(std::vector<D3D12_STATE_SUBOBJECT> &unwrapped_sub_objects, std::span<const D3D12_STATE_SUBOBJECT> wrapped_sub_objects);

		void UnwrapStructObjects(D3D12_STATE_SUBOBJECT &unwrapped_sub_object, std::vector<D3D12_STATE_SUBOBJECT> &unwrapped_sub_objects, std::span<const D3D12_STATE_SUBOBJECT> wrapped_sub_objects);

		void UnwrapStructObjects(D3D12_SUBOBJECT_TO_EXPORTS_ASSOCIATION &unwrapped_exports_association, std::vector<D3D12_STATE_SUBOBJECT> &unwrapped_sub_objects, std::span<const D3D12_STATE_SUBOBJECT> wrapped_sub_objects);
    }
}
















