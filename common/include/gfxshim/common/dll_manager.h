//
// Created by ZZK on 2024/11/16.
//

#pragma once

#include <gfxshim/common/base.h>

namespace gfxshim
{
	template <typename DispatchTableType>
	struct DLLManager
	{
	public:
		using LoadLibraryStrategy = void(*)(LibraryHandle, DispatchTableType *);
		using InitializeFuncFromTracer = bool(*)(DispatchTableType *);
		using ReleaseFuncFromTracer = void(*)(DispatchTableType *);

	public:
		bool Initialize(std::string_view system_library_path, std::string_view tracer_library_path, std::string_view initialize_func_name, LoadLibraryStrategy load_library_strategy);

		void Release(std::string_view release_func_name);

		const DispatchTableType &QueryDispatchTable() const;

	private:
		DispatchTableType dispatch_table{};
		LibraryHandle system_dll = nullptr;
		LibraryHandle tracer_dll = nullptr;
	};

	template<typename DispatchTableType>
	bool DLLManager<DispatchTableType>::Initialize(const std::string_view system_library_path, const std::string_view tracer_library_path,
													const std::string_view initialize_func_name, LoadLibraryStrategy load_library_strategy)
	{
		system_dll = LoadLibraryA(system_library_path.data());
		if (!system_dll)
		{
			return false;
		}
		load_library_strategy(system_dll, &dispatch_table);

		tracer_dll = LoadLibraryA(tracer_library_path.data());
		if (!tracer_dll)
		{
			return false;
		}
		auto initialize_func_ptr = reinterpret_cast<InitializeFuncFromTracer>(GetProcAddress(tracer_dll, initialize_func_name.data()));
		if (!initialize_func_ptr)
		{
			return false;
		}
		initialize_func_ptr(&dispatch_table);

		return true;
	}

	template<typename DispatchTableType>
	void DLLManager<DispatchTableType>::Release(const std::string_view release_func_name)
	{
		if (!tracer_dll)
		{
			auto release_func_ptr = reinterpret_cast<ReleaseFuncFromTracer>(GetProcAddress(tracer_dll, release_func_name.data()));
			if (!release_func_ptr)
			{
				release_func_ptr(&dispatch_table);
			}
			FreeLibrary(tracer_dll);
			tracer_dll = nullptr;
		}
		if (!system_dll)
		{
			FreeLibrary(system_dll);
			system_dll = nullptr;
		}
	}

	template<typename DispatchTableType>
	const DispatchTableType &DLLManager<DispatchTableType>::QueryDispatchTable() const
	{
		return dispatch_table;
	}
}
