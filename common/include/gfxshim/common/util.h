//
// Created by ZZK on 2025/4/20.
//

#pragma once

#include <gfxshim/common/base.h>

namespace gfxshim::util
{
#define FOREACH_DUMP_FILE_TYPE(func) \
		func(Binary)                 \
		func(DDS)                    \
		func(BMP)                    \
		func(JPEG)

	enum class DumpFileType : uint8_t
	{
#define DUMP_FILE_TYPE_ENUM_FUNCTION(name) name,
		FOREACH_DUMP_FILE_TYPE(DUMP_FILE_TYPE_ENUM_FUNCTION)
#undef DUMP_FILE_TYPE_ENUM_FUNCTION
	};

	inline constexpr std::string ConvertDumpFileTypeToString(DumpFileType file_type)
	{
		switch (file_type)
		{
#define DUMP_FILE_TYPE_ENUM_STRING(name) case DumpFileType::name: return #name;
			FOREACH_DUMP_FILE_TYPE(DUMP_FILE_TYPE_ENUM_STRING)
#undef DUMP_FILE_TYPE_ENUM_STRING
			default: return "Unknown DumpFileType";
		}
	}

	inline DumpFileType QueryDumpFileType(const std::string &variable_name)
	{
		static std::unordered_map<std::string, DumpFileType> s_string_dump_map{
			{ ConvertDumpFileTypeToString(DumpFileType::Binary), DumpFileType::Binary },
			{ ConvertDumpFileTypeToString(DumpFileType::DDS), DumpFileType::DDS },
			{ ConvertDumpFileTypeToString(DumpFileType::BMP), DumpFileType::BMP },
			{ ConvertDumpFileTypeToString(DumpFileType::JPEG), DumpFileType::JPEG }
		};

		if (s_string_dump_map.contains(variable_name))
		{
			return s_string_dump_map[variable_name];
		}

		return DumpFileType::Binary;
	}

	inline std::string QueryEnvironmentVariable(const std::string_view variable_name)
	{
		const auto buffer_size = GetEnvironmentVariableA(variable_name.data(), nullptr, 0);
		if (buffer_size == 0U)
		{
			return "";
		}
		std::vector<char> buffer(buffer_size);
		GetEnvironmentVariableA(variable_name.data(), buffer.data(), buffer_size);
		return std::string{ buffer.data() };
	}
}
