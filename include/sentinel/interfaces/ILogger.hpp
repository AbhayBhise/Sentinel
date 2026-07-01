#ifndef SENTINEL_INTERFACES_ILOGGER_HPP
#define SENTINEL_INTERFACES_ILOGGER_HPP

#include <string>
#include <source_location>

namespace sentinel {
namespace interfaces {

/**
 * @brief Interface for logging operations.
 */
class ILogger {
public:
    virtual ~ILogger() = default;

    /**
     * @brief Log an informational message.
     * @param msg The message to log.
     * @param loc The source location of the log call.
     */
    virtual void info(const std::string& msg, const std::source_location& loc = std::source_location::current()) = 0;

    /**
     * @brief Log a warning message.
     * @param msg The message to log.
     * @param loc The source location of the log call.
     */
    virtual void warn(const std::string& msg, const std::source_location& loc = std::source_location::current()) = 0;

    /**
     * @brief Log an error message.
     * @param msg The message to log.
     * @param loc The source location of the log call.
     */
    virtual void error(const std::string& msg, const std::source_location& loc = std::source_location::current()) = 0;

    /**
     * @brief Log a critical message.
     * @param msg The message to log.
     * @param loc The source location of the log call.
     */
    virtual void critical(const std::string& msg, const std::source_location& loc = std::source_location::current()) = 0;

    /**
     * @brief Log a debug message.
     * @param msg The message to log.
     * @param loc The source location of the log call.
     */
    virtual void debug(const std::string& msg, const std::source_location& loc = std::source_location::current()) = 0;
};

} // namespace interfaces
} // namespace sentinel

#endif // SENTINEL_INTERFACES_ILOGGER_HPP
