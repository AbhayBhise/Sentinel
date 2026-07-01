#include "sentinel/logger/Logger.hpp"
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/daily_file_sink.h>
#include <filesystem>
#include <iostream>

namespace sentinel {
namespace logger {

Logger& Logger::getInstance() {
    static Logger instance;
    return instance;
}

void Logger::init(const std::string& log_level_str, const std::string& log_dir) {
    try {
        if (!std::filesystem::exists(log_dir)) {
            std::filesystem::create_directories(log_dir);
        }

        auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        
        // Daily rotating file sink (rotates at midnight)
        std::string log_file = log_dir + "/sentinel.log";
        auto file_sink = std::make_shared<spdlog::sinks::daily_file_sink_mt>(log_file, 0, 0);

        std::vector<spdlog::sink_ptr> sinks {console_sink, file_sink};
        
        m_spdlogger = std::make_shared<spdlog::logger>("sentinel", sinks.begin(), sinks.end());
        
        // Set the custom format
        // [%Y-%m-%d %H:%M:%S.%e] [%P:%t] [%^%l%$] [%s:%#] %v
        m_spdlogger->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%P:%t] [%^%l%$] [%s:%#] %v");
        
        // Parse log level
        spdlog::level::level_enum level = spdlog::level::info;
        if (log_level_str == "debug") level = spdlog::level::debug;
        else if (log_level_str == "warn") level = spdlog::level::warn;
        else if (log_level_str == "error") level = spdlog::level::err;
        else if (log_level_str == "critical") level = spdlog::level::critical;
        
        m_spdlogger->set_level(level);
        
        // Flush on error or worse
        m_spdlogger->flush_on(spdlog::level::err);
        
        spdlog::register_logger(m_spdlogger);
        spdlog::set_default_logger(m_spdlogger);
        
    } catch (const spdlog::spdlog_ex& ex) {
        std::cerr << "Logger initialization failed: " << ex.what() << std::endl;
    }
}

void Logger::shutdown() {
    if (m_spdlogger) {
        m_spdlogger->flush();
        spdlog::drop_all();
        m_spdlogger.reset();
    }
}

static spdlog::source_loc to_spdlog_loc(const std::source_location& loc) {
    return spdlog::source_loc{loc.file_name(), static_cast<int>(loc.line()), loc.function_name()};
}

void Logger::info(const std::string& msg, const std::source_location& loc) {
    if (m_spdlogger) m_spdlogger->log(to_spdlog_loc(loc), spdlog::level::info, msg);
}

void Logger::warn(const std::string& msg, const std::source_location& loc) {
    if (m_spdlogger) m_spdlogger->log(to_spdlog_loc(loc), spdlog::level::warn, msg);
}

void Logger::error(const std::string& msg, const std::source_location& loc) {
    if (m_spdlogger) m_spdlogger->log(to_spdlog_loc(loc), spdlog::level::err, msg);
}

void Logger::critical(const std::string& msg, const std::source_location& loc) {
    if (m_spdlogger) m_spdlogger->log(to_spdlog_loc(loc), spdlog::level::critical, msg);
}

void Logger::debug(const std::string& msg, const std::source_location& loc) {
    if (m_spdlogger) m_spdlogger->log(to_spdlog_loc(loc), spdlog::level::debug, msg);
}

} // namespace logger
} // namespace sentinel
