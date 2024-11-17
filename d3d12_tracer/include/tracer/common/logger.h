//
// Created by ZZK on 2024/7/21.
//

#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace gfxshim
{
    class Logger
    {
    private:
        Logger();

    public:
        Logger(const Logger &) = delete;
        Logger &operator=(const Logger &) = delete;
        Logger(Logger &&) = delete;
        Logger &operator=(Logger &&) = delete;

        static Logger &get();

        std::shared_ptr<spdlog::logger> &call_logger();

    private:
        std::shared_ptr<spdlog::logger> m_core_logger;
    };
}

// Logger macros
#if !defined(D3D12_WRAPPER_TRACE)
#define D3D12_WRAPPER_TRACE(...)		::gfxshim::Logger::get().call_logger()->trace(__VA_ARGS__)
#endif

#if !defined(D3D12_WRAPPER_DEBUG)
#define D3D12_WRAPPER_DEBUG(...)		::gfxshim::Logger::get().call_logger()->debug(__VA_ARGS__)
#endif

#if !defined(D3D12_WRAPPER_INFO)
#define D3D12_WRAPPER_INFO(...)		    ::gfxshim::Logger::get().call_logger()->info(__VA_ARGS__)
#endif

#if !defined(D3D12_WRAPPER_WARN)
#define D3D12_WRAPPER_WARN(...)		    ::gfxshim::Logger::get().call_logger()->warn(__VA_ARGS__)
#endif

#if !defined(D3D12_WRAPPER_ERROR)
#define D3D12_WRAPPER_ERROR(...)		::gfxshim::Logger::get().call_logger()->error(__VA_ARGS__)
#endif

#if !defined(D3D12_WRAPPER_CRITICAL)
#define D3D12_WRAPPER_CRITICAL(...)	    ::gfxshim::Logger::get().call_logger()->critical(__VA_ARGS__); throw std::runtime_error("D3D12Wrapper fatal error!")
#endif

#if !defined(D3D12_WRAPPER_ASSERT)
#define D3D12_WRAPPER_ASSERT(expression, ...)	\
if (!(expression)) { ::gfxshim::Logger::get().call_logger()->error(__VA_ARGS__); } assert(expression)
#endif