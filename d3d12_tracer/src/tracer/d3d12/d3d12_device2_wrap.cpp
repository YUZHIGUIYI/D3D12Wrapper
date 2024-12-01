//
// Created by ZZK on 2024/7/20.
//

#include <tracer/d3d12/d3d12_device2_wrap.h>
#include <tracer/core/wrapper_creators.h>

namespace gfxshim
{
    ID3D12Device2Wrapper::ID3D12Device2Wrapper(const IID &riid, IUnknown *object)
    : ID3D12Device1Wrapper(riid, object)
    {

    }

    ID3D12Device2Wrapper::~ID3D12Device2Wrapper() = default;

    HRESULT STDMETHODCALLTYPE ID3D12Device2Wrapper::CreatePipelineState(
            const D3D12_PIPELINE_STATE_STREAM_DESC* pDesc,
            REFIID riid,
            void** ppPipelineState)
    {
		// TODO: check unwrap state stream desc
		if (pDesc != nullptr && pDesc->SizeInBytes > 0U && pDesc->pPipelineStateSubobjectStream != nullptr)
		{
			D3D12_PIPELINE_STATE_STREAM_DESC unwrap_pipeline_state_stream_desc{};
			std::vector<uint8_t> pipeline_state_stream(pDesc->SizeInBytes);
			std::memcpy(pipeline_state_stream.data(), pDesc->pPipelineStateSubobjectStream, pDesc->SizeInBytes);
			unwrap_pipeline_state_stream_desc.SizeInBytes = pDesc->SizeInBytes;
			unwrap_pipeline_state_stream_desc.pPipelineStateSubobjectStream = pipeline_state_stream.data();
			auto start = pipeline_state_stream.data();
			size_t offset = 0U;
			while (offset < pDesc->SizeInBytes)
			{
				auto current = start + offset;
				const auto sub_object_type = *reinterpret_cast<D3D12_PIPELINE_STATE_SUBOBJECT_TYPE *>(current);
				// Only the root signature sub-object requires object unwrapping, the rest of the sub-objects only require an offset increment
				if (sub_object_type == D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_ROOT_SIGNATURE)
				{
					auto sub_object = reinterpret_cast<Dx12SignatureSubObject *>(current);
					sub_object->value = encode::GetWrappedObject<ID3D12RootSignature>(sub_object->value);
					offset += sizeof(Dx12SignatureSubObject);
					break;
				}
				switch (sub_object_type)
				{
					case D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_VS:
					case D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_PS:
					case D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_DS:
					case D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_HS:
					case D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_GS:
					case D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_CS:
					case D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_AS:
					case D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_MS:
					    offset += sizeof(Dx12ShaderBytecodeSubObject);
					    break;
					case D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_STREAM_OUTPUT:
						offset += sizeof(Dx12StreamOutputSubObject);
						break;
					case D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_BLEND:
						offset += sizeof(Dx12BlendSubObject);
						break;
					case D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_SAMPLE_MASK:
					case D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_NODE_MASK:
						offset += sizeof(Dx12UintSubObject);
						break;
					case D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_RASTERIZER:
						offset += sizeof(Dx12RasterizerSubObject);
						break;
					case D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_DEPTH_STENCIL:
						offset += sizeof(Dx12DepthStencilSubObject);
						break;
					case D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_INPUT_LAYOUT:
						offset += sizeof(Dx12InputLayoutSubObject);
						break;
					case D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_IB_STRIP_CUT_VALUE:
						offset += sizeof(Dx12StripCutSubObject);
						break;
					case D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_PRIMITIVE_TOPOLOGY:
						offset += sizeof(Dx12PrimitiveTopologySubObject);
						break;
					case D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_RENDER_TARGET_FORMATS:
						offset += sizeof(Dx12RenderTargetFormatsSubObject);
						break;
					case D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_DEPTH_STENCIL_FORMAT:
						offset += sizeof(Dx12FormatSubObject);
						break;
					case D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_SAMPLE_DESC:
						offset += sizeof(Dx12SampleDescSubObject);
						break;
					case D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_CACHED_PSO:
						offset += sizeof(Dx12CachedPSOSubObject);
						break;
					case D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_FLAGS:
						offset += sizeof(Dx12TypeFlagsSubObject);
						break;
					case D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_DEPTH_STENCIL1:
						offset += sizeof(Dx12DepthStencil1SubObject);
						break;
					case D3D12_PIPELINE_STATE_SUBOBJECT_TYPE_VIEW_INSTANCING:
						offset += sizeof(Dx12ViewInstancingSubObject);
						break;
					default:
						 // Type is unrecognized. Write an invalid enum value so the decoder know the data is incomplete,
						offset = pDesc->SizeInBytes;
						break;
				}
			}

			const auto result = GetWrappedObjectAs<ID3D12Device2>()->CreatePipelineState(&unwrap_pipeline_state_stream_desc, riid, ppPipelineState);
			if (SUCCEEDED(result))
			{
				encode::WrapObject(riid, ppPipelineState);
			}
			return result;
		}
		const auto result = GetWrappedObjectAs<ID3D12Device2>()->CreatePipelineState(pDesc, riid, ppPipelineState);
		if (SUCCEEDED(result))
		{
			encode::WrapObject(riid, ppPipelineState);
		}
		return result;
    }
}