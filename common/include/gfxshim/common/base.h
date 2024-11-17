//
// Created by ZZK on 2024/11/16.
//

#pragma once

#include <directx/d3d12.h>
#include <directx/d3dcommon.h>
#include <dxgi.h>
#include <dxgi1_3.h>
#include <dxgi1_6.h>
#include <windef.h>
#include <atomic>
#include <unordered_map>
#include <string>
#include <string_view>
#include <vector>
#include <cassert>
#include <span>
#include <memory>
#include <mutex>
#include <type_traits>
#include <concepts>
#include <wrl/client.h>

#if defined(__GNUC__) || defined(__clang__)
#define SHIM_FUNC_SIGNATURE __PRETTY_FUNCTION__
#elif defined(_MSC_VER)
#define SHIM_FUNC_SIGNATURE __FUNCSIG__
#else
#define SHIM_FUNC_SIGNATURE __func__
#endif

#if defined(max)
#undef max
#endif

#if defined(min)
#undef min
#endif

#if defined(near)
#undef near
#endif

#if defined(far)
#undef far
#endif

namespace gfxshim
{
	template <typename T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;

	using LibraryHandle = HMODULE;
}

