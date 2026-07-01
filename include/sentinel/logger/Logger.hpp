#ifndef SENTINEL_LOGGER_LOGGER_HPP
#define SENTINEL_LOGGER_LOGGER_HPP

#include "sentinel/interfaces/ILogger.hpp"
#include <spdlog/spdlog.h>
#include <memory>
#include <string>

namespace sentinel {
namespace logger {

/**
 * @brief Thread-safe Singleton Logger implementation wrapping spdlog.
 */
class Logger : public interfaces::ILogger {
public:
    /**
     * @brief Get the singleton instance.
     * @return Logger& 
     */
    static Logger& getInstance();

    /**
     * @brief Initialize the logger with a specific log level and directory.
     * @param log_level The minimum log level (e.g., "info", "debug").
     * @param log_dir The directory where log files will be saved.
     */
    void init(const std::string& log_level, const std::string& log_dir);

    /**
     * @brief Shut down the logger and flush all sinks.
     */
    void shutdown();

    // ILogger implementation
    void info(const std::string& msg, const std::source_location& loc = std::source_location::current()) override;
    void warn(const std::string& msg, const std::source_location& loc = std::source_location::current()) override;
    void error(const std::string& msg, const std::source_location& loc = std::source_location::current()) override;
    void critical(const std::string& msg, const std::source_location& loc = std::source_location::current()) override;
    void debug(const std::string& msg, const std::source_location& loc = std::source_location::current()) override;

    // Helper static methods for ease of use
    static void logInfo(const std::string& msg, const std::source_location& loc = std::source_location::current()) { getInstance().info(msg, loc); }
    static void logWarn(const std::string& msg, const std::source_location& loc = std::source_location::current()) { getInstance().warn(msg, loc); }
    static void logError(const std::string& msg, const std::source_location& loc = std::source_location::current()) { getInstance().error(msg, loc); }
    static void logCritical(const std::string& msg, const std::source_location& loc = std::source_location::current()) { getInstance().critical(msg, loc); }
    static void logDebug(const std::string& msg, const std::source_location& loc = std::source_location::current()) { getInstance().debug(msg, loc); }

private:
    Logger() = default;
    ~Logger() override = default;

    // Prevent copying and assignment
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    std::shared_ptr<spdlog::logger> m_spdlogger;
};

} // namespace logger
} // namespace sentinel

#endif // SENTINEL_LOGGER_LOGGER_HPP
