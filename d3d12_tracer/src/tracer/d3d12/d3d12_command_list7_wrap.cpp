#include <tracer/d3d12/d3d12_command_list7_wrap.h>

namespace gfxshim
{
    ID3D12GraphicsCommandList7Wrapper::ID3D12GraphicsCommandList7Wrapper(const IID &riid, IUnknown *object)
    : ID3D12GraphicsCommandList6Wrapper(riid, object)
    {

    }

    ID3D12GraphicsCommandList7Wrapper::~ID3D12GraphicsCommandList7Wrapper() = default;

    void STDMETHODCALLTYPE ID3D12GraphicsCommandList7Wrapper::Barrier(
            UINT32 NumBarrierGroups,
            const D3D12_BARRIER_GROUP* pBarrierGroups)
    {
		// TODO: check unwrap structs
		if (NumBarrierGroups > 0U && pBarrierGroups != nullptr)
		{
			std::vector<D3D12_BARRIER_GROUP> unwrap_barrier_groups(NumBarrierGroups);
			std::vector<D3D12_TEXTURE_BARRIER> texture_barriers{};
			std::vector<D3D12_BUFFER_BARRIER> buffer_barriers{};
			std::memcpy(unwrap_barrier_groups.data(), pBarrierGroups, sizeof(D3D12_BARRIER_GROUP) * NumBarrierGroups);
			for (uint32_t i = 0U; i < NumBarrierGroups; ++i)
			{
				auto &&barrier_group = pBarrierGroups[i];
				if (barrier_group.Type == D3D12_BARRIER_TYPE_TEXTURE && barrier_group.NumBarriers > 0U)
				{
					texture_barriers.resize(barrier_group.NumBarriers);
					std::memcpy(texture_barriers.data(), barrier_group.pTextureBarriers, barrier_group.NumBarriers * sizeof(D3D12_TEXTURE_BARRIER));
					for (uint32_t j = 0U; j < barrier_group.NumBarriers; ++j)
					{
						texture_barriers[j].pResource = encode::GetWrappedObject<ID3D12Resource>(barrier_group.pTextureBarriers[j].pResource);
					}
					unwrap_barrier_groups[i].pTextureBarriers = texture_barriers.data();
				} else if (barrier_group.Type == D3D12_BARRIER_TYPE_BUFFER && barrier_group.NumBarriers > 0U)
				{
					buffer_barriers.resize(barrier_group.NumBarriers);
					std::memcpy(buffer_barriers.data(), barrier_group.pBufferBarriers, barrier_group.NumBarriers * sizeof(D3D12_BUFFER_BARRIER));
					for (uint32_t j = 0U; j < barrier_group.NumBarriers; ++j)
					{
						buffer_barriers[j].pResource = encode::GetWrappedObject<ID3D12Resource>(barrier_group.pBufferBarriers[j].pResource);
					}
					unwrap_barrier_groups[i].pBufferBarriers = buffer_barriers.data();
				}
			}
			return GetWrappedObjectAs<ID3D12GraphicsCommandList7>()->Barrier(NumBarrierGroups, unwrap_barrier_groups.data());
		}
        return GetWrappedObjectAs<ID3D12GraphicsCommandList7>()->Barrier(NumBarrierGroups, pBarrierGroups);
    }
}

void STDMETHODCALLTYPE WrappedID3D12GraphicsCommandList::Barrier(UINT32 NumBarrierGroups,
                        const D3D12_BARRIER_GROUP *pBarrierGroups)
{
    m_pList7->Barrier(NumBarrierGroups, pBarrierGroups);
}