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
	constexpr IID IID_Device_11_On_12 = { 0x77ACCE80, 0x638E, 0x4E65, { 0x88, 0x95, 0xC1, 0xF2, 0x33, 0x86, 0x86, 0x3E } };
	constexpr IID IID_Queue_11_On_12 = { 0x0EC870A6, 0x5D7E, 0x4C22, { 0x8C, 0xFC, 0x5B, 0xAA, 0xE0, 0x76, 0x16, 0xED } };

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
}
    namespace gfxshim::encode
    {
		template <typename T>
		requires std::is_base_of_v<IUnknown, T>
		T *GetWrappedObject(T *wrapped_object)
		{
			if (wrapped_object != nullptr)
			{
				// For the unwrapped object, QueryInterface below would always return fail/no-interface result;
				// for the wrapped object, QueryInterface below would always return successful result, and get the unwrapped unknown object
				void *unknown_object = nullptr;
				if (auto result = wrapped_object->QueryInterface(IID_IUnknown_Wrapper, &unknown_object); SUCCEEDED(result))
				{
					return static_cast<T *>(unknown_object);
				}
				return wrapped_object;
			}
			return nullptr;
		}

		template <typename T>
		requires std::is_base_of_v<IUnknown, T>
		const T *GetWrappedObject(const T *wrapped_object)
		{
			if (wrapped_object != nullptr)
			{
				// For unwrapped object, QueryInterface below would always return fail/no-interface result;
				// for the wrapped object, QueryInterface below would always return successful result, and get the unwrapped unknown object
				void *unknown_object = nullptr;
				if (auto result = const_cast<T *>(wrapped_object)->QueryInterface(IID_IUnknown_Wrapper, &unknown_object); SUCCEEDED(result))
				{
					return static_cast<const T *>(unknown_object);
				}
				return wrapped_object;
			}
			return nullptr;
		}

		void UnwrapStructObjects(std::vector<D3D12_STATE_SUBOBJECT> &unwrapped_sub_objects, std::span<const D3D12_STATE_SUBOBJECT> wrapped_sub_objects);

		void UnwrapStructObjects(D3D12_STATE_SUBOBJECT &unwrapped_sub_object, std::vector<D3D12_STATE_SUBOBJECT> &unwrapped_sub_objects, std::span<const D3D12_STATE_SUBOBJECT> wrapped_sub_objects);

		void UnwrapStructObjects(D3D12_SUBOBJECT_TO_EXPORTS_ASSOCIATION &unwrapped_exports_association, std::vector<D3D12_STATE_SUBOBJECT> &unwrapped_sub_objects, std::span<const D3D12_STATE_SUBOBJECT> wrapped_sub_objects);
    }

















