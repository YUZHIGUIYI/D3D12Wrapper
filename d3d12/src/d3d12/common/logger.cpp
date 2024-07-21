//
// Created by ZZK on 2024/7/21.
//

#include <d3d12/common/logger.h>

namespace gfxshim
{
    Logger& Logger::get()
    {
        static Logger logger{};
        return logger;
    }

    Logger::Logger()
    {
        // One console sink
        // One sink and one log file only, different patterns
        std::vector<spdlog::sink_ptr> log_sinks;
        log_sinks.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
        log_sinks.emplace_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>("D3D12Shim.log", true));

        log_sinks[0]->set_pattern("%^[%T] [%n]: %v%$");
        log_sinks[1]->set_pattern("[%D %T] [%l] [%n]: %v");

        m_core_logger = std::make_shared<spdlog::logger>("D3D12Shim", std::begin(log_sinks), std::end(log_sinks));
        spdlog::register_logger(m_core_logger);
        m_core_logger->set_level(spdlog::level::debug);
        m_core_logger->flush_on(spdlog::level::debug);
    }

    std::shared_ptr<spdlog::logger> &Logger::call_logger()
    {
        return m_core_logger;
    }
}