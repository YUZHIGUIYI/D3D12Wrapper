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
		auto roaming_path = std::getenv("APPDATA");
		std::string redirect_library_path{};
		if (roaming_path != nullptr)
		{
			std::string dll_user_target = std::string{ roaming_path } + "\\" + std::string{ "gfxshim" };
			std::string dll_runtime_target = dll_user_target + "\\" + std::string{ "dx-runtimes" };
			if (!std::filesystem::exists(dll_user_target))
			{
				std::filesystem::create_directory(dll_user_target);
			}
			if (!std::filesystem::exists(dll_runtime_target))
			{
				std::filesystem::create_directory(dll_runtime_target);
			}
			std::string rename_library_path = std::string{ system_library_path };
			auto dot_pos = rename_library_path.find_last_of('.');
			auto back_slash_pos = rename_library_path.find_last_of('\\');
			if (dot_pos == std::string::npos || back_slash_pos == std::string::npos)
			{
				return false;
			}
			auto system_library_directory = rename_library_path.substr(0, back_slash_pos);
			rename_library_path = dll_runtime_target + "\\"  + rename_library_path.substr(back_slash_pos + 1, dot_pos - back_slash_pos - 1) + "_ms.dll";
			if (!std::filesystem::exists(rename_library_path))
			{
				if (!std::filesystem::copy_file(system_library_path, rename_library_path))
				{
					return false;
				}
			}
			auto redirect_core_library_path = dll_runtime_target + "\\D3D12Core.dll";
			auto system_core_library_path = system_library_directory + "\\D3D12Core.dll";
			if (!std::filesystem::exists(redirect_core_library_path))
			{
				if (!std::filesystem::copy_file(system_core_library_path, redirect_core_library_path))
				{
					return false;
				}
			}
			redirect_library_path = rename_library_path;
		}
		system_dll = LoadLibraryA(redirect_library_path.data());
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
